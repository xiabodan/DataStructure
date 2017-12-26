package com.putao.ptx.appstatuscollect;

import android.content.Context;
import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;
import android.util.SparseArray;

/**
 * Database operator
 * Created by putao on 17-7-15.
 */
public class DBManager extends SQLiteOpenHelper {
    private static final String DB_NAME = "statsdb.db";
    private static final int DB_VERSION = 1;
    private static final String TABLE_NAME = "stats";
    private static final String[] COLUMNS = new String[]{"uid", "stats"};
    private static DBManager sDBManager;
    private final Context mContext;

    public static synchronized DBManager getInstance(Context context) {
        if (sDBManager == null) {
            sDBManager = new DBManager(context);
        }
        return sDBManager;
    }

    private DBManager(Context context) {
        super(context, DB_NAME, null, DB_VERSION);
        mContext = context;
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        String sql = "create table if not exists " + TABLE_NAME +
                " (uid integer primary key, stats text)";
        db.execSQL(sql);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
    }

    /**
     * update all app stats data to db
     * @param store The app stats data.
     */
    public void updateLastStatsToDb(SparseArray<StatElement> store) {
        final int NC = store.size();
        for (int ic = 0; ic < NC; ic++) {
            final int uid = store.keyAt(ic);
            final StatElement element = store.valueAt(ic);
            final String stats = element.toJson();
            if (!updateRowData(uid, stats)) {
                insertRowDate(uid, stats);
            }
        }
    }

    /**
     * initialization db
     */
    public void initTable() {
    }

    /**
     * update a row of data
     * @param uid The app uid.
     * @param stats a app stats json data.
     * @return true if update success
     */
    public boolean updateRowData(int uid, String stats) {
        int affected = 0;
        SQLiteDatabase db = null;
        try {
            db = getWritableDatabase();
            db.beginTransaction();

            // replace uid row
            ContentValues cv = new ContentValues();
            cv.put("uid", uid);
            cv.put("stats", stats);
            affected = db.update(TABLE_NAME, cv,
                    "uid = ?", new String[]{String.valueOf(uid)});
            db.setTransactionSuccessful();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (db != null) {
                db.endTransaction();
                db.close();
            }
        }

        return (affected > 0);
    }

    /**
     * insert a row of data
     * @param uid The app uid.
     * @param stats a app stats json data.
     */
    public void insertRowDate(int uid, String stats) {
        SQLiteDatabase db = null;

        try {
            db = getWritableDatabase();
            db.beginTransaction();

            // insert into row(uid, stats) values (uid, stats);
            ContentValues contentValues = new ContentValues();
            contentValues.put("uid", uid);
            contentValues.put("stats", stats);
            db.insertOrThrow(TABLE_NAME, null, contentValues);
            db.setTransactionSuccessful();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (db != null) {
                db.endTransaction();
                db.close();
            }
        }
    }

    /**
     * get all app stats json data from db
     * @return SparseArray for all stats data
     */
    public SparseArray<StatElement> getLastStorageStatsFromDb() {
        SparseArray<StatElement> element = new SparseArray<>();
        SQLiteDatabase db = null;
        Cursor cursor = null;
        try {
            db = getReadableDatabase();
            // select * from table
            cursor = db.query(TABLE_NAME, COLUMNS, null, null, null, null, null);

            if (cursor.getCount() > 0) {
                while (cursor.moveToNext()) {
                    int uid = cursor.getInt(cursor.getColumnIndex("uid"));
                    String stats = (cursor.getString(cursor.getColumnIndex("stats")));
                    StatElement last = StatElement.fromJson(stats);
                    element.put(uid, last);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (cursor != null) {
                cursor.close();
            }
            if (db != null) {
                db.close();
            }
        }

        return element;
    }

    /**
     * delete a row data
     * @param uid The line that will be deleted.
     */
    public void deleteRowData(int uid) {
        SQLiteDatabase db = null;
        try {
            db = getWritableDatabase();
            db.beginTransaction();

            // delete from table where uid
            db.delete(TABLE_NAME, "uid = ?", new String[]{String.valueOf(uid)});
            db.setTransactionSuccessful();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (db != null) {
                db.endTransaction();
                db.close();
            }
        }
    }
}
