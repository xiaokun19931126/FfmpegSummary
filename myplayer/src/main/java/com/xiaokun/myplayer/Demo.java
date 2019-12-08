package com.xiaokun.myplayer;

/**
 * Created by 肖坤 on 2019/12/2.
 *
 * @author 肖坤
 * @date 2019/12/2
 */
public class Demo {

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

}
