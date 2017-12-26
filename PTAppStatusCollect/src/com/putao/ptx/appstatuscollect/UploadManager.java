package com.putao.ptx.appstatuscollect;

import android.content.Context;
import android.util.Log;
import android.util.SparseArray;

import com.putao.minisdk.MiniCollectionSdk;

public class UploadManager {
    public static final String TAG = "UploadManager";
    public static final String UPLOAD_LOG_TYPE = "paios_power";
    private static final boolean DEBUG = false;
    private static UploadManager sUploadManager;
    private final Context mContext;
    private StatsProxy mProxy = null;
    private DBManager mDbManager = null;
    private SparseArray<StatElement> mCurrentStats;
    private SparseArray<StatElement> mStorageStats;
    private MiniCollectionSdk minisdk = null;  // use for upload data to service

    public static synchronized UploadManager getInstance(Context context) {
        if (sUploadManager == null) {
            sUploadManager = new UploadManager(context);
        }
        return sUploadManager;
    }

    private UploadManager(Context context) {
        mContext = context;
        mProxy = StatsProxy.getInstance(context);
        mDbManager = DBManager.getInstance(context);

        // step 1: get previous stats from database
        mStorageStats = mDbManager.getLastStorageStatsFromDb();

        // config minisdk
        if (minisdk == null) {
            minisdk = MiniCollectionSdk.getInstance(context);
        }
        minisdk.setOnBindChangedListener(new MiniCollectionSdk.OnBindChangedListener() {
            public void onBindSuccess() {
                Log.d(TAG, "onBindSuccess...");
                minisdk.setDataInfo("com.putao.ptx.appstatuscollect", "23", "custom");
                minisdk.didFinishLaunched("85bfac7251c93e16b7b946ea5eded05d",
                        "164594b08b39e5f74a891699da8aff62");
            }
        });
        minisdk.bindService();  // 绑定后台service.
    }

    /**
     * collect and uplaod stats
     * @param screenStats
     * 0: if current state is screen off, just storage stats to db
     * 1: if current state is screen on, upload stats to server
     * -1: if current state is alarm wakeup, upload stats to server
     * 2: if current state is boot, nothing to be done
     */
    public void collectAndUploadJsonData(int screenStats) {
        Log.i(TAG, "collectAndUploadJsonData screenStats " + screenStats);

        if (screenStats == BootReceiver.BOOT) {
            // do nothing when power on
            return;
        }

        // step 2: get all status from BatteryStatsService
        mCurrentStats = mProxy.getCurrentStats(0);

        if (screenStats == BootReceiver.SCREEN_OFF) {
            // save the state when the screen off, as a benchmark
            mDbManager.updateLastStatsToDb(mCurrentStats);
            // update local cache status
            getDiffCurrentAndLast();
        } else if ((screenStats == BootReceiver.SCREEN_ON) ||
                (screenStats == BootReceiver.ALARM_WAKEUP)) {
            // step 3: calculate The difference between the two data
            SparseArray<StatElement> mDifferenceStats = getDiffCurrentAndLast();

            // step 4: upload difference data to server
            uploadStatsToServer(mDifferenceStats);

            // step 5: update last storage stats to database
            mDbManager.updateLastStatsToDb(mCurrentStats);
        }
    }

    public void closeUploadChannel() {
        minisdk.exit();
    }

    /**
     * calculate difference between the current and previous status
     * @return The difference between the current and previous status
     */
    private SparseArray<StatElement> getDiffCurrentAndLast() {
        SparseArray<StatElement> diff = new SparseArray<>();
        final int NC = mCurrentStats.size();
        for (int ic = 0; ic < NC; ic++) {
            int uid = mCurrentStats.keyAt(ic);
            StatElement element = mCurrentStats.valueAt(ic).clone();
            StatElement current = element.clone();
            boolean isChanged = true;
            if (mStorageStats.indexOfKey(uid) >= 0) {
                StatElement last = mStorageStats.get(uid).clone();
                // 计算当前状态与前一次状态的差值
                isChanged = current.subStatsFromPre(last);
                current.setTimeSlot(current.getEndTimestamp() - last.getEndTimestamp());
            }

            if (isChanged == true) {
                diff.put(uid, current);
            }
            // update local history stats
            mStorageStats.put(uid, element);
        }

        return diff;
    }

    /**
     * upload difference between the current and previous status
     * @param diff difference between the current and previous status
     */
    private void uploadStatsToServer(SparseArray<StatElement> diff) {
        final int NC = diff.size();
        for (int ic = 0; ic < NC; ic++) {
            StatElement element = diff.valueAt(ic);
            String uploadJson = element.toUploadJson();
            if (DEBUG) {
                Log.d(TAG, "uploadJson=" + uploadJson);
            }
            // TODO: need implement upload operations
            // Connect the upload SDK
            minisdk.addExtInfo(uploadJson, UPLOAD_LOG_TYPE);
        }
    }
}
