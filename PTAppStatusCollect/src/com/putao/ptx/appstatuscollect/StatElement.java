package com.putao.ptx.appstatuscollect;

import android.util.Log;

import java.util.HashMap;
import java.util.Map;
import java.util.Iterator;
import java.util.Set;

import org.json.JSONStringer;
import org.json.JSONObject;
import org.json.JSONException;

/**
 * Contains all upload data and its operations
 * Detailed escalation format see README
 * Created by putao on 17-7-15.
 */
public class StatElement {

    /**
     * The process uid, do not upload uid
     * Not upload
     */
    private int mUid;

    /**
     * upload type definition
     */
    private String mType;

    /**
     * app version name
     */
    private String mVersionName;

    /**
     * The Memory usage, Unit(kb)
     */
    private int mMemoryUsage;

    /**
     * The intervals between current and last collect status
     */
    private long mTimeSlot;

    /**
     * The current acquisition time
     */
    private long mEndTimestamp;

    /**
     * The package name
     */
    private String mPackageName;

    /**
     * The process count of App
     */
    private int mProcessCount;

    /**
     * The partial wakelock count
     */
    private int mWakelockCount;

    /**
     * The partial wakelock total time(ms)
     */
    private long mWakelockTime;

    /**
     * The alarm wakeup times
     */
    private int mAlarmWakeups;

    /**
     * The network usage, unit(bytes)
     */
    private long mNetworkUsage;

    /**
     * The bluetooth power usage(mAh)
     */
    private double mBluetoothUsage;

    /**
     * The camera power usage(mAh)
     */
    private double mCameraUsage;

    /**
     * The cpu power usage(mAh)
     */
    private double mCpuPowerUsage;

    /**
     * All Sensors of this app
     * String means sensor type name, Long means use this sensor time(ms)
     * Detailed escalation format see README
     */
    Map<String, Long> mSensors;

    public StatElement() {
        mSensors = new HashMap<String, Long>();
        setType("power");
    }

    public void setUid(int uid) {
        mUid = uid;
    }

    public void setTimeSlot(long time) {
        mTimeSlot = time;
    }

    public void setTimestamp() {
        mEndTimestamp = System.currentTimeMillis();
    }

    public void setTimestamp(long time) {
        mEndTimestamp = time;
    }

    public void setPackageName(String packageName) {
        if (packageName == null) {
            mPackageName = "unknow";
        } else {
            mPackageName = packageName;
        }
    }

    public void setProcessCount(int count) {
        mProcessCount = count;
    }

    public void setWakelockCount(int count) {
        mWakelockCount = count;
    }

    public void setWakelockTime(long time) {
        mWakelockTime = time;
    }

    public void setAlarmWakeups(int wakeups) {
        mAlarmWakeups = wakeups;
    }

    public void setNetworkUsage(long bytes) {
        mNetworkUsage = bytes;
    }

    public void setBluetoothUsage(double time) {
        mBluetoothUsage = time;
    }

    public void setCameraUsage(double time) {
        mCameraUsage = time;
    }

    public void setCpuPowerUsage(double time) {
        mCpuPowerUsage = time;
    }

    public void setSensors(String type, long time) {
        mSensors.put(type, time);
    }

    public void setMemoryUsage(int size) {
        mMemoryUsage = size;
    }

    public void setType(String type) {
        mType = type;
    }

    public void setVersionName(String versionName) {
        if (versionName == null) {
            mVersionName = "";
        } else {
            mVersionName = versionName;
        }
    }

    public int getUid() {
        return mUid;
    }

    public long getStartTimestamp() {
        return mTimeSlot;
    }

    public long getEndTimestamp() {
        return mEndTimestamp;
    }

    public String getPackageName() {
        return mPackageName;
    }

    public int getProcessCount() {
        return mProcessCount;
    }

    public int getWakelockCount() {
        return mWakelockCount;
    }

    public long getWakelockTime() {
        return mWakelockTime;
    }

    public int getAlarmWakeups() {
        return mAlarmWakeups;
    }

    public long getNetworkUsage() {
        return mNetworkUsage;
    }

    public double getBluetoothUsage() {
        return mBluetoothUsage;
    }

    public double getCameraUsage() {
        return mCameraUsage;
    }

    public double getCpuPowerUsage() {
        return mCpuPowerUsage;
    }

    public Map<String,Long> getSensors() {
        return mSensors;
    }

    public int getMemoryUsage() {
        return mMemoryUsage;
    }

    public String getVersionName() {
        return mVersionName;
    }

    public String getType() {
        return mType;
    }

    /**
     * Clone an identical object
     * @return the clone object
     */
    public StatElement clone() {
        StatElement clone = new StatElement();
        clone.setUid(getUid());
        clone.setVersionName(getVersionName());
        clone.setType(getType());
        clone.setMemoryUsage(getMemoryUsage());
        clone.setTimeSlot(getStartTimestamp());
        clone.setTimestamp(getEndTimestamp());
        clone.setPackageName(getPackageName());
        clone.setProcessCount(getProcessCount());
        clone.setWakelockCount(getWakelockCount());
        clone.setWakelockTime(getWakelockTime());
        clone.setAlarmWakeups(getAlarmWakeups());
        clone.setNetworkUsage(getNetworkUsage());
        clone.setBluetoothUsage(getBluetoothUsage());
        clone.setCameraUsage(getCameraUsage());
        clone.setCpuPowerUsage(getCpuPowerUsage());

        for (Map.Entry<String, Long> ent : getSensors().entrySet()) {
            String type = ent.getKey();
            long time = ent.getValue();
            clone.mSensors.put(type, time);
        }

        return clone;
    }

    /**
     * calculate the difference between the two StatElement element
     * @param ref Be subtracted StatElement object
     * @return false: The current state is the same as the previous status
     *         true: The current status is different from the previous status
     */
    public boolean subStatsFromPre(StatElement ref) {
        if (mUid != ref.getUid())
            return false;

        boolean isModify = false;
        isModify |= (mMemoryUsage != ref.getMemoryUsage());  // upload memory usage
        isModify |= (mWakelockCount -= ref.getWakelockCount()) > 0;
        isModify |= (mWakelockTime -= ref.getWakelockTime()) > 0;
        isModify |= (mAlarmWakeups -= ref.getAlarmWakeups()) > 0;
        isModify |= (mNetworkUsage -= ref.getNetworkUsage()) > 0;
        isModify |= (mBluetoothUsage -= ref.getBluetoothUsage()) > 0;
        isModify |= (mCameraUsage -= ref.getCameraUsage()) > 0;
        isModify |= (mCpuPowerUsage -= ref.getCpuPowerUsage()) > 0;
        for (Map.Entry<String, Long> ent : ref.getSensors().entrySet()) {
            String type = ent.getKey();
            long time = ent.getValue();
            if (mSensors.containsKey(type) && time != mSensors.get(type)) {
                mSensors.put(type, mSensors.get(type) - time);
                isModify |= true;
            }
        }

        return isModify;
    }

    /**
     * convert StatElement to string
     * @return string data
     */
    public String toString() {
        String sensor = "";
        for (Map.Entry<String, Long> ent : mSensors.entrySet()) {
            String type = ent.getKey();
            long time = ent.getValue();
            sensor += " Sensor[" + type + " " + time + "]";
        }

        return "AppStats(uid=" + mUid + ", appVersion =" + mVersionName
                + ", memoryUsage=" + mMemoryUsage + ", timeSlot=" + mTimeSlot
                + ", timestamp=" + mEndTimestamp + ", packageName=" + mPackageName
                + ", processCount=" + mProcessCount + ", wakelockCount=" + mWakelockCount
                + ", wakelockTime=" + mWakelockTime + ", alarmWakeups=" + mAlarmWakeups
                + ", networkUsage=" + mNetworkUsage + ", bluetoothusage=" + mBluetoothUsage
                + ", cameraUsage=" + mCameraUsage + ", cpuPowerUsage=" + mCpuPowerUsage
                + sensor + " )";
    }

    private void addBaseKey(JSONStringer js) {
        try {
            js.key("appVersion").value(mVersionName);
            js.key("type").value(mType);
            js.key("memoryUsage").value(mMemoryUsage);
            js.key("timeSlot").value(mTimeSlot);
            js.key("timestamp").value(mEndTimestamp);
            js.key("packageName").value(mPackageName);
            js.key("processCount").value(mProcessCount);
            js.key("wakelockCount").value(mWakelockCount);
            js.key("wakelockTime").value(mWakelockTime);
            js.key("alarmWakeups").value(mAlarmWakeups);
            js.key("networkUsage").value(mNetworkUsage);
            js.key("bluetoothUsage").value(mBluetoothUsage);
            js.key("cameraUsage").value(mCameraUsage);
            js.key("cpuPowerUsage").value(mCpuPowerUsage);
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    /**
     * convert StatElement to json format
     * @return stats json data, just use upload
     */
    public String toUploadJson() {
        JSONStringer js = new JSONStringer();
        try {
            js.object();
            addBaseKey(js);
            for (Map.Entry<String, Long> ent : mSensors.entrySet()) {
                String type = ent.getKey();
                long time = ent.getValue();
                js.key(type).value(time);
            }
            js.endObject();
        } catch (JSONException e) {
            e.printStackTrace();
        }

        return js.toString();
    }

    /**
     * convert StatElement to json format
     * @return stats json data, just use db storage
     */
    public String toJson() {
        JSONStringer js = new JSONStringer();
        try {
            js.object();
            js.key("uid").value(mUid);
            addBaseKey(js);
            JSONObject object = new JSONObject();
            for (Map.Entry<String, Long> ent : mSensors.entrySet()) {
                String type = ent.getKey();
                long time = ent.getValue();
                object.put(type, time);
                // js.key(type).value(time);
            }
            js.key("sensor").value(object);
            js.endObject();
        } catch (JSONException e) {
            e.printStackTrace();
        }

        return js.toString();
    }

    /**
     * restore StatElement from json, just use db read
     * @param stats json data
     */
    public static StatElement fromJson(String stats) {
        StatElement element = new StatElement();
        try {
            JSONObject object = new JSONObject(stats);
            element.mUid = object.getInt("uid");
            element.mType = object.getString("type");
            element.mVersionName = object.getString("appVersion");
            element.mMemoryUsage = object.getInt("memoryUsage");
            element.mTimeSlot = object.getLong("timeSlot");
            element.mEndTimestamp = object.getLong("timestamp");
            element.mPackageName = object.getString("packageName");
            element.mProcessCount = object.getInt("processCount");
            element.mWakelockTime = object.getLong("wakelockTime");
            element.mWakelockCount = object.getInt("wakelockCount");
            element.mAlarmWakeups = object.getInt("alarmWakeups");
            element.mNetworkUsage = object.getLong("networkUsage");
            element.mBluetoothUsage = object.getDouble("bluetoothUsage");
            element.mCameraUsage = object.getDouble("cameraUsage");
            element.mCpuPowerUsage = object.getDouble("cpuPowerUsage");

            JSONObject sensor = object.getJSONObject("sensor");
            Set<String> sensors = sensor.keySet();
            for (Iterator it = sensors.iterator(); it.hasNext(); ) {
                String type = (String) it.next();
                element.mSensors.put(type, sensor.getLong(type));
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }

        return element;
    }
}
