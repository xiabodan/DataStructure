package com.putao.ptx.appstatuscollect;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.SystemClock;
import android.util.Log;

/**
 * Created by lizengyun on 17-7-19.
 */

public class InfoCollectReceiver extends BroadcastReceiver {
    private static final String TAG = "InfoCollectReceiver";
    private static String State = "ScreenState";

    @Override
    public void onReceive(Context context, Intent intent) {
        Log.d(TAG,"onReceive");
        if (intent.getAction().equals(Intent.ACTION_SCREEN_OFF)) {
            Log.d(TAG, "startAlarm");
            int interval = 30 * 60 * 1000;  // 30分钟Alarm时间
            long triggerTime = System.currentTimeMillis() + interval;
            Intent i = new Intent(context.getApplicationContext(), CollectAndUploadService.class);
            PendingIntent sender = PendingIntent.getService(context.getApplicationContext(), 0, i, 0);
            AlarmManager manager = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);
            manager.setRepeating(AlarmManager.RTC_WAKEUP, triggerTime, interval, sender);
            i.putExtra(State, BootReceiver.SCREEN_OFF);
            context.startService(i);
        } else if (intent.getAction().equals(Intent.ACTION_SCREEN_ON)) {
            Log.d(TAG, "stopAlarm");
            Intent i = new Intent(context.getApplicationContext(), CollectAndUploadService.class);
            PendingIntent sender = PendingIntent.getService(context.getApplicationContext(), 0, i, 0);
            AlarmManager manager = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);
            manager.cancel(sender);
            i.putExtra(State, BootReceiver.SCREEN_ON);
            context.startService(i);
        }
    }
}
