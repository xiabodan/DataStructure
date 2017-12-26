package com.putao.ptx.appstatuscollect;

import android.content.Intent;
import android.content.Context;
import android.content.BroadcastReceiver;
import android.os.SystemProperties;
import android.util.Log;

public class BootReceiver extends BroadcastReceiver {
    public static final String TAG = "BootReceiver";
    public static final int SCREEN_OFF = 0;
    public static final int SCREEN_ON = 1;
    public static final int ALARM_WAKEUP = -1;
    public static final int BOOT = 2;

    /**
     * 用Extra区别startService(CollectAndUploadService)的intent状态:
     * 0 表示收到灭屏广播时的intent
     * 1 表示收到亮屏广播时的intent
     * 2 表示收到系统启动时的intent
     */
    private static String State = "ScreenState";

    @Override
    public void onReceive(Context context, Intent intent) {
        Log.d(TAG, "BootReceiver is start up");
        startLogcatd();
        Intent i = new Intent(context.getApplicationContext(),
                CollectAndUploadService.class);
        i.putExtra(State, BOOT);
        context.startService(i);
    }


    /**
     * 启动logcatd service
     */
    private void startLogcatd() {
        SystemProperties.set("logd.logpersistd", "logcatd");
    }
}
