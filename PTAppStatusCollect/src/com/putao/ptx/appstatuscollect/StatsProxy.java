package com.putao.ptx.appstatuscollect;

import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.BatteryStats;
import android.os.BatteryStats.Uid;
import android.os.BatteryStats.Counter;
import android.os.BatteryStats.Timer;
import android.os.UserManager;
import android.os.SystemClock;
import android.os.Bundle;
import android.util.SparseArray;
import android.util.Log;
import android.util.ArrayMap;
import android.hardware.Sensor;
import android.hardware.SensorManager;

import com.android.internal.os.PowerProfile;
import com.android.internal.os.BatterySipper;
import com.android.internal.os.BatterySipper.DrainType;
import android.os.Debug;
import android.app.ActivityManager;
import com.android.internal.os.BatteryStatsHelper;

import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.ArrayList;

/**
 * Get all status from BatteryStatsService and ActivityManagerService
 * Created by putao on 17-7-15.
 */
public class StatsProxy {
    private static final String TAG = "StatsProxy";
    private static final boolean DEBUG = false;

    private static StatsProxy sStatsProxy;
    private final Object mLock = new Object();
    private int mStatsType = BatteryStats.STATS_CURRENT;
    private final Context mContext;
    private UserManager mUm;
    private PowerProfile mProfile;
    private BatteryStatsHelper mStatsHelper;
    private BatteryStats mStats;
    private Map<Integer, List<Integer>> mRunProcessPids;
    private Map<Integer, String> mRunProcessName;

    private static final String SKIPLIST =
            "android.uid.calendar,android.media,android.uid.systemui,android.uid.shared";

    private final static int[] mSensorsHandle = {
            Sensor.TYPE_ACCELEROMETER,
            Sensor.TYPE_MAGNETIC_FIELD,
            Sensor.TYPE_ORIENTATION,
            Sensor.TYPE_GYROSCOPE,
            Sensor.TYPE_LIGHT,
            Sensor.TYPE_PROXIMITY,
            Sensor.TYPE_GRAVITY,
            Sensor.TYPE_LINEAR_ACCELERATION,
            Sensor.TYPE_ROTATION_VECTOR,
            Sensor.TYPE_MAGNETIC_FIELD_UNCALIBRATED,
            Sensor.TYPE_GYROSCOPE_UNCALIBRATED,
            Sensor.TYPE_GEOMAGNETIC_ROTATION_VECTOR,
            -10000 };  // gps

    private StatsProxy(Context context) {
        mContext = context;
        mUm = (UserManager) mContext.getSystemService(Context.USER_SERVICE);
        mProfile = new PowerProfile(mContext);
        mRunProcessPids = new HashMap<Integer, List<Integer>>();
        mRunProcessName = new HashMap<Integer, String>();
    }

    public static synchronized StatsProxy getInstance(Context context) {
        if (sStatsProxy == null) {
            sStatsProxy = new StatsProxy(context);
        }
        return sStatsProxy;
    }

    /**
     * get a current stats reference
     * @param iSort Whether to sort results
     * @return current stats map of uid key
     */
    public synchronized SparseArray<StatElement> getCurrentStats(int iSort) {
        SparseArray<StatElement> currentStats = new SparseArray<>();

        mStatsHelper = new BatteryStatsHelper(mContext);
        mStatsHelper.create(new Bundle());
        mStats = mStatsHelper.getStats();

        // get all app stats
        getRunningAppProcesses();

        final SparseArray<? extends Uid> uidStats = mStats.getUidStats();
        final int NU = uidStats.size();
        for (int iu = 0; iu < NU; iu++) {
            final Uid u = uidStats.valueAt(iu);
            final int uid = u.getUid();
            if (uid <= 10000) {
                continue;  // 不统计uid小于10000的, 小于10000的是系统进程，暂不统计
            }

            String packageName = getPackageNameForUid(uid);
            if (SKIPLIST.contains(packageName)) {
                continue;
            }

            StatElement element = new StatElement();
            initSensorData(element);
            element.setPackageName(packageName);
            element.setUid(uid);
            element.setTimestamp();
            getAppVersion(element, uid);
            getUidMemoryUsage(element, uid);
            getCurrentWakelockStat(element, u);
            getCurrentSensorStat(element, u);
            getCurrentNetworkStat(element, u);
            getCurrentOtherStat(element, u);
            getCurrentProcessStat(element, u);
            getCurrentPackageStat(element, u);
            getCurrentBluetoothUsage(element, u);
            getCurrentCpuUsage(element, u);

            if (DEBUG) Log.i(TAG, element.toString());
            currentStats.put(uid, element);
        }

        return currentStats;
    }

    /**
     * Init sensor data to 0
     * @param element StatElement element
     */
    private void initSensorData(StatElement element) {
        for (int i = 0; i < mSensorsHandle.length; i++) {
            element.setSensors(getSensorName(mSensorsHandle[i]), 0);
        }
    }

    /**
     * get camera video audio flashlight time
     * @param element StatElement element
     * @param u containing the statistics for this app.
     * @return element StatElement element
     */
    public StatElement getCurrentOtherStat(StatElement element, Uid u) {
        final long elapsedRealtime = SystemClock.elapsedRealtime() * 1000;

        final double cameraPowerOnAvg = mProfile.getAveragePower(PowerProfile.POWER_CAMERA);
        BatteryStats.Timer cameraTimer = u.getCameraTurnedOnTimer();
        if (cameraTimer != null) {
            final long cameraTimeUs = cameraTimer.getTotalTimeLocked(elapsedRealtime, mStatsType);
            final int cameraCount = cameraTimer.getCountLocked(mStatsType);
            double cameraPowerMah = ((cameraTimeUs / 1000) * cameraPowerOnAvg) / (1000 * 60 * 60);
            element.setCameraUsage(cameraPowerMah);
        }

        return element;
    }

    /**
     * get network usage bytes, only care wifi usage
     */
    public StatElement getCurrentNetworkStat(StatElement element, Uid u) {
        final long wifiRxPackets = u.getNetworkActivityBytes(BatteryStats.NETWORK_WIFI_RX_DATA, mStatsType);
        final long wifiTxPackets = u.getNetworkActivityBytes(BatteryStats.NETWORK_WIFI_TX_DATA, mStatsType);

        element.setNetworkUsage(wifiTxPackets + wifiRxPackets);

        return element;
    }

    /**
     * Calculate sensor time, count, type
     */
    public StatElement getCurrentSensorStat(StatElement element, Uid u) {
        final long elapsedRealtime = SystemClock.elapsedRealtime() * 1000;
        long sensorCount = 0;
        long sensorTimeUs = 0;
        final SparseArray<? extends BatteryStats.Uid.Sensor> sensors = u.getSensorStats();
        final int NSE = sensors.size();
        for (int ise = 0; ise < NSE; ise++) {
            final Uid.Sensor se = sensors.valueAt(ise);
            final int sensorNumber = sensors.keyAt(ise);
            final Timer timer = se.getSensorTime();
            final int handle = se.getHandle();
            if (timer != null) {
                sensorTimeUs = timer.getTotalTimeLocked(elapsedRealtime, mStatsType);
                sensorCount = timer.getCountLocked(mStatsType);
                String sensorType = getSensorName(handle);
                if (sensorType != null) {
                    element.setSensors(sensorType, (sensorTimeUs + 499) / 1000);
                }
            }
        }

        return element;
    }

    /**
     * get sensor name of handle from SensorManager
     * @param handle sensor type
     * @return sensor name
     */
    private String getSensorName(int handle) {
        // TODO: Maybe should get from SensorManager
        switch (handle) {
            case Sensor.TYPE_ACCELEROMETER:
                return "accelerometerSensor";
            case Sensor.TYPE_MAGNETIC_FIELD:
                return "magnetometerSensor";
            case Sensor.TYPE_ORIENTATION:
                return "orientationSensor";
            case Sensor.TYPE_GYROSCOPE:
                return "gyroscopeSensor";
            case Sensor.TYPE_LIGHT:
                return "lightSensor";
            case Sensor.TYPE_PROXIMITY:
                return "proximitySensor";
            case Sensor.TYPE_GRAVITY:
                return "gravitySensor";
            case Sensor.TYPE_LINEAR_ACCELERATION:
                return "linearAccelerometerSensor";
            case Sensor.TYPE_ROTATION_VECTOR:
                return "rotationVectorSensor";
            case Sensor.TYPE_MAGNETIC_FIELD_UNCALIBRATED:
                return "uncalibratedMagnetometerSensor";
            case Sensor.TYPE_GYROSCOPE_UNCALIBRATED:
                return "uncalibratedGyroscopeSensor";
            case Sensor.TYPE_GEOMAGNETIC_ROTATION_VECTOR:
                return "geomagneticRotationVectorSensor";
            case -10000:
                return "gpsSensor";
            default :
                return null;
        }
    }

    /**
     * get package name of uid from PackageManager
     * @param uid app uid
     * @return The package name of this uid
     */
    private String getPackageNameForUid(int uid) {
        PackageManager pm = mContext.getPackageManager();
        String name = pm.getNameForUid(uid);
        String[] names = {""};
        if (name != null) {
            names = name.split(":");
        }
        return names[0];
    }

    /**
     * get wakelock time/count
     */
    public StatElement getCurrentWakelockStat(StatElement element, Uid u) {
        long uSecBatteryTime = mStats.computeBatteryRealtime(
                SystemClock.elapsedRealtime() * 1000, mStatsType);

        // calculate wakelock time, count
        long wakelockTimeUs = 0;
        int wakelockCount = 0;
        final ArrayMap<String, ? extends BatteryStats.Uid.Wakelock> wakelockStats
                = u.getWakelockStats();
        final int size = wakelockStats.size();
        for (int i = 0; i < size; i++) {
            final BatteryStats.Uid.Wakelock wakelock = wakelockStats.valueAt(i);
            String wakelockName = wakelockStats.keyAt(i);
            // Only care about partial wake locks since full wake locks
            // are canceled when the user turns the screen off.
            BatteryStats.Timer timer = wakelock.getWakeTime(BatteryStats.WAKE_TYPE_PARTIAL);
            if (timer != null) {
                wakelockTimeUs += timer.getTotalTimeLocked(uSecBatteryTime, mStatsType);
                wakelockCount += timer.getCountLocked(mStatsType);
            }
        }
        element.setWakelockTime((wakelockTimeUs + 500) / 1000);
        element.setWakelockCount(wakelockCount);

        return element;
    }

    /**
     * get process number and system/user time
     */
    public StatElement getCurrentProcessStat(StatElement element, Uid u) {
        final long systemCpuTimeUs = u.getSystemCpuTimeUs(mStatsType);
        final long userCpuTimeUs = u.getUserCpuTimeUs(mStatsType);
        final long powerCpuMaUs = u.getCpuPowerMaUs(mStatsType);

        final ArrayMap<String, ? extends  BatteryStats.Uid.Proc> processStats
                = u.getProcessStats();
        final int processCount = processStats.size();
        element.setProcessCount(processCount);
        // get all process list from the current app
        // has not yet joined the json, maybe used later
        for (int ipr = processCount - 1; ipr >= 0; ipr--) {
            final Uid.Proc ps = processStats.valueAt(ipr);

            long userTime = ps.getUserTime(mStatsType);
            long systemTime = ps.getSystemTime(mStatsType);
            long foregroundTime = ps.getForegroundTime(mStatsType);
            int starts = ps.getStarts(mStatsType);
            final int numCrashes = ps.getNumCrashes(mStatsType);
            final int numAnrs = ps.getNumAnrs(mStatsType);
        }

        return element;
    }

    /**
     * get package alarm wakeup
     */
    public StatElement getCurrentPackageStat(StatElement element, Uid u) {
        final long rawUptime = SystemClock.uptimeMillis() * 1000;
        final long batteryUptime = mStats.getBatteryUptime(rawUptime);
        int alarmCount = 0;
        final ArrayMap<String, ? extends BatteryStats.Uid.Pkg> packageStats = u.getPackageStats();
        for (int ipkg = packageStats.size() - 1; ipkg >= 0; ipkg--) {
            final Uid.Pkg ps = packageStats.valueAt(ipkg);
            final ArrayMap<String, ? extends Counter> alarms = ps.getWakeupAlarmStats();
            for (int iwa = alarms.size() - 1; iwa >= 0; iwa--) {
                String name = alarms.keyAt(iwa);
                alarmCount += alarms.valueAt(iwa).getCountLocked(mStatsType);
            }
            element.setAlarmWakeups(alarmCount);

            // get all service list from the current app
            // has not yet joined the json, maybe used later
            final ArrayMap<String, ? extends  Uid.Pkg.Serv> serviceStats = ps.getServiceStats();
            for (int isvc = serviceStats.size() - 1; isvc >= 0; isvc--) {
                final BatteryStats.Uid.Pkg.Serv ss = serviceStats.valueAt(isvc);
                final long startTime = ss.getStartTime(batteryUptime, mStatsType);
                final int starts = ss.getStarts(mStatsType);
                final int launches = ss.getLaunches(mStatsType);
            }
        }

        return element;
    }

    /**
     * get bluetooth power usage of app, unit mAh
     */
    public StatElement getCurrentBluetoothUsage(StatElement element, Uid u) {
        final double idleMa = mProfile.getAveragePower(
                PowerProfile.POWER_BLUETOOTH_CONTROLLER_IDLE);
        final double rxMa = mProfile.getAveragePower(
                PowerProfile.POWER_BLUETOOTH_CONTROLLER_RX);
        final double txMa = mProfile.getAveragePower(
                PowerProfile.POWER_BLUETOOTH_CONTROLLER_TX);

        final BatteryStats.ControllerActivityCounter counter
                = u.getBluetoothControllerActivity();
        if (counter == null) {
            element.setBluetoothUsage(0);
            return element;
        }

        final long idleTimeMs = counter.getIdleTimeCounter().getCountLocked(mStatsType);
        final long rxTimeMs = counter.getRxTimeCounter().getCountLocked(mStatsType);
        final long txTimeMs = counter.getTxTimeCounters()[0].getCountLocked(mStatsType);
        final long totalTimeMs = idleTimeMs + txTimeMs + rxTimeMs;
        double powerMah = counter.getPowerCounter().getCountLocked(mStatsType)
                / (double)(1000 * 60 * 60);

        if (powerMah == 0) {
            // Some devices do not report the power, so calculate it.
            powerMah = ((idleTimeMs * idleMa) + (rxTimeMs * rxMa) + (txTimeMs * txMa))
                    / (1000 * 60 * 60);
        }
        element.setBluetoothUsage(powerMah);
        if (DEBUG && powerMah != 0) {
            Log.d(TAG, "Bluetooth active: time=" + (totalTimeMs)
                    + " power=" + BatteryStatsHelper.makemAh(powerMah));
        }
        // Log.i(TAG, " getCurrentBluetoothUsage totalTimeMs= " + totalTimeMs);

        return element;
    }

    /**
     * get cpu power usage of app, unit mAh
     */
    public StatElement getCurrentCpuUsage(StatElement element, Uid u) {
        // Aggregate total time spent on each cluster.
        long cpuTimeMs = (u.getUserCpuTimeUs(mStatsType) + u.getSystemCpuTimeUs(mStatsType)) / 1000;
        long totalTime = 0;
        final int numClusters = mProfile.getNumCpuClusters();
        for (int cluster = 0; cluster < numClusters; cluster++) {
            final int speedsForCluster = mProfile.getNumSpeedStepsInCpuCluster(cluster);
            for (int speed = 0; speed < speedsForCluster; speed++) {
                totalTime += u.getTimeAtCpuSpeed(cluster, speed, mStatsType);
            }
        }
        totalTime = Math.max(totalTime, 1);

        double cpuPowerMaMs = 0;
        for (int cluster = 0; cluster < numClusters; cluster++) {
            final int speedsForCluster = mProfile.getNumSpeedStepsInCpuCluster(cluster);
            for (int speed = 0; speed < speedsForCluster; speed++) {
                final double ratio = (double) u.getTimeAtCpuSpeed(cluster, speed, mStatsType) /
                        totalTime;
                final double cpuSpeedStepPower = ratio * cpuTimeMs *
                        mProfile.getAveragePowerForCpu(cluster, speed);
                if (DEBUG && ratio != 0) {
                    Log.d(TAG, "UID " + u.getUid() + ": CPU cluster #" + cluster + " step #"
                            + speed + " ratio=" + BatteryStatsHelper.makemAh(ratio) + " power="
                            + BatteryStatsHelper.makemAh(cpuSpeedStepPower / (60 * 60 * 1000)));
                }
                cpuPowerMaMs += cpuSpeedStepPower;
            }
        }
        double cpuPowerMah = cpuPowerMaMs / (60 * 60 * 1000);
        element.setCpuPowerUsage(cpuPowerMah);

        if (DEBUG && cpuPowerMaMs != 0) {
            Log.d(TAG, "UID " + u.getUid() + ": cpu total power="
                    + BatteryStatsHelper.makemAh(cpuPowerMaMs / (60 * 60 * 1000)));
        }

        return element;
    }

    /**
     * get the version according to PackageName
     */
    public StatElement getAppVersion(StatElement element, int uid) {
        try {
            String packageName = getPackageNameForUid(uid);
            PackageManager manager = mContext.getPackageManager();
            PackageInfo info = manager.getPackageInfo(packageName,
                    PackageManager.GET_DISABLED_COMPONENTS |
                    PackageManager.GET_UNINSTALLED_PACKAGES |
                    PackageManager.GET_SIGNATURES);
            element.setVersionName(info.versionName);
            return element;
        } catch (Exception e) {
            element.setVersionName("");
            e.printStackTrace();
        }

        return element;
    }

    public StatElement getUidMemoryUsage(StatElement element, int uid) {
        if (uid == 0) {
            return element;
        }
        List<Integer> pid = getPidsOfApp(uid);
        if (pid != null) {
            element.setMemoryUsage(getUidMemoryUsage(pid));
        }
        return element;
    }

    public int getUidMemoryUsage(List<Integer> list) {
        ActivityManager activityManager = (ActivityManager) mContext.getSystemService(Context.ACTIVITY_SERVICE);
        int memUsage = 0;
        Map<Integer, String> pidMap = new TreeMap<Integer, String>();
        for (int num:list) {
            pidMap.put(num, getPidName(num));
        }
        Collection<Integer> keys = pidMap.keySet();
        long begin = System.currentTimeMillis();
        for (int key : keys) {
            int []pids = new int[1];
            pids[0] = key;
            Debug.MemoryInfo[] memoryInfoArray = activityManager.getProcessMemoryInfo(pids);
            memUsage += memoryInfoArray[0].getTotalPss();
        }
        long cost = System.currentTimeMillis() - begin;

        if (DEBUG && cost != 0) {
            Log.i(TAG, "getUidMemoryUsage cost time " + cost);
        }

        return memUsage;
    }

    /**
     * get current running process, classification as uid
     */
    private void getRunningAppProcesses() {
        ActivityManager am = (ActivityManager)
                mContext.getSystemService(Context.ACTIVITY_SERVICE);
        List<RunningAppProcessInfo> processList = am.getRunningAppProcesses();

        for (int i = 0; i < processList.size(); i++) {
            final int uid = processList.get(i).uid;
            final int pid = processList.get(i).pid;
            mRunProcessName.put(pid, processList.get(i).processName);
            if (!mRunProcessPids.containsKey(uid)) {
                List<Integer> pidList = new ArrayList<Integer>();
                pidList.add(pid);
                mRunProcessPids.put(uid, pidList);
                continue;
            }
            mRunProcessPids.get(uid).add(pid);
        }
    }

    /**
     * get package name of pid
     * @param pid the pid of process
     * @return package name of this pid
     */
    private String getPidName(int pid) {
        return mRunProcessName.get(pid);
    }

    /**
     * get all pid of this uid
     * @param uid the uid of app
     * @return list of uid key
     */
    private List<Integer> getPidsOfApp(int uid) {
        return mRunProcessPids.get(uid);
    }
}
