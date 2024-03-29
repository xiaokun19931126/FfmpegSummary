package com.xiaokun.myplayer;

import android.text.TextUtils;
import android.util.Log;

/**
 * Created by 肖坤 on 2019/12/2.
 *
 * @author 肖坤
 * @date 2019/12/2
 */
public class Demo {

    private static final String TAG = "Demo";

    // Used to load the 'native-lib' library on application startup.
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

    //public native String stringFromJNI();

    public native void testFFmpeg();

    private String source;

    public Demo() {
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

    public native void n_prepared(String source);

}
