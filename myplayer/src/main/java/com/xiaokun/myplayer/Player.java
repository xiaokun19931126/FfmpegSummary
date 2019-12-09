package com.xiaokun.myplayer;

import android.text.TextUtils;
import android.util.Log;

/**
 * Created by xiaokun on 2019/12/9.
 *
 * @author xiaokun
 * @date 2019/12/9
 */
public class Player {

    private static final String TAG = "Player";

    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("avutil-55");
        System.loadLibrary("swresample-2");
        System.loadLibrary("avcodec-57");
        System.loadLibrary("avformat-57");
        System.loadLibrary("swscale-4");
        System.loadLibrary("postproc-54");
        System.loadLibrary("avfilter-6");
        System.loadLibrary("avdevice-57");
    }

    private String source;

    public Player() {
    }

    public void setSource(String source) {
        this.source = source;
    }

    private FOnPrepareListener mFOnPrepareListener;

    public void setFOnPrepareListener(FOnPrepareListener FOnPrepareListener) {
        mFOnPrepareListener = FOnPrepareListener;
    }

    public void prepared() {
        if (TextUtils.isEmpty(source)) {
            MyLog.d("source can not be empty");
            return;
        }

        new Thread(new Runnable() {
            @Override
            public void run() {
                n_prepared(source);
            }
        }).start();
    }

    /**
     * c++回调java方法类似反射
     */
    public void onCallPrepared() {
        Log.d(TAG, "[onCallPrepared] ");
        if (mFOnPrepareListener != null) {
            mFOnPrepareListener.onPrepare();
        }
    }

    private native void n_prepared(String source);


    public void start() {
        n_start();
    }

    private native void n_start();

}
