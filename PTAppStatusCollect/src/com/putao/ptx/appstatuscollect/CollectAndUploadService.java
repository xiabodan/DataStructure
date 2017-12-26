package com.putao.ptx.appstatuscollect;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.IBinder;
import android.os.PowerManager;
import android.util.Log;

import java.util.Date;

public class CollectAndUploadService extends Service {
    public static final String TAG = "CollectAndUploadService";
    private static String State = "ScreenState";
    private InfoCollectReceiver mInfoCollectReceiver = new InfoCollectReceiver();
    private UploadManager mUploader;

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        return null;
    }

    @Override
    public void onCreate() {
        Log.i(TAG, "onCreate");
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(Intent.ACTION_SCREEN_OFF);
        intentFilter.addAction(Intent.ACTION_SCREEN_ON);
        registerReceiver(mInfoCollectReceiver, intentFilter);
        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.d(TAG, "onStartCommand");
        PowerManager pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
        PowerManager.WakeLock wl = pm.newWakeLock(
                PowerManager.PARTIAL_WAKE_LOCK, "StatusCollect");
        wl.setReferenceCounted(false);
        wl.acquire(2000);  // 设置超时2秒钟

        // trigger data update and upload json to server
        int screenState = BootReceiver.ALARM_WAKEUP;
        if (intent != null) {
            screenState = intent.getIntExtra(State, BootReceiver.ALARM_WAKEUP);
        }
        mUploader = UploadManager.getInstance(getApplicationContext());
        mUploader.collectAndUploadJsonData(screenState);
        // mUploader.closeUploadChannel();

        Log.i(TAG, "executed at " + new Date().toString());
        wl.release();

        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public void onDestroy() {
        Log.d(TAG, "onDestroy");
        unregisterReceiver(mInfoCollectReceiver);
        super.onDestroy();
    }
}
