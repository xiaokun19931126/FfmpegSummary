package com.xiaokun.myplayer;

import android.util.Log;

/**
 * Created by xiaokun on 2019/12/8.
 *
 * @author xiaokun
 * @date 2019/12/8
 */
public class MyLog {

    private static final String TAG = "xiaokun";
    private static boolean mIsDebug = true;

    public static void setIsDebug(boolean debug) {
        mIsDebug = debug;
    }

    public static void d(String msg) {
        if (mIsDebug) {
            Log.d(TAG, msg);
        }
    }

    public static void e(String msg) {
        if (mIsDebug) {
            Log.e(TAG, msg);
        }
    }


}
