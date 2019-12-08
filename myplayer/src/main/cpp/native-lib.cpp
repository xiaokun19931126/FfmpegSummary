#include <jni.h>
#include <string>
#include "android/log.h"


extern "C" {
#include "include/libavformat/avformat.h"
#include "include/libavcodec/avcodec.h"
#include "include/libavutil/avutil.h"
}


#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"xiaokun",FORMAT,##__VA_ARGS__);

//com.xiaokun.myplayer.Demo

extern "C"
JNIEXPORT void JNICALL
Java_com_xiaokun_myplayer_Demo_testFFmpeg(JNIEnv *env, jobject thiz) {

    av_register_all();
    AVCodec *c_temp = av_codec_next(NULL);
    while (c_temp != NULL) {
        switch (c_temp->type) {
            case AVMEDIA_TYPE_VIDEO:
                LOGI("[Video]:%s", c_temp->name);
                break;
            case AVMEDIA_TYPE_AUDIO:
                LOGI("[Audio]:%s", c_temp->name);
                break;
            default:
                LOGI("[Other]:%s", c_temp->name);
                break;
        }
        c_temp = c_temp->next;
    }

}