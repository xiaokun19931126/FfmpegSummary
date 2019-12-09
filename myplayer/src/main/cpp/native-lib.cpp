#include <jni.h>
#include <string>
#include <syslog.h>
#include "AndroidLog.h"
#include "android/log.h"
#include "MyAudio.h"

extern "C" {
#include "include/libavformat/avformat.h"
#include "include/libavcodec/avcodec.h"
#include "include/libavutil/avutil.h"
}

//com.xiaokun.myplayer.Demo
//解码线程
pthread_t decodeThread = NULL;
AVFormatContext *avFormatContext = NULL;
MyAudio *myAudio;
_JavaVM *javaVm;
jmethodID jmethodId;
JNIEnv *jniEnv;
jobject jobj;
jstring urlStr;

bool getResult(char *url);

extern "C"
JNIEXPORT void JNICALL
Java_com_xiaokun_myplayer_Demo_testFFmpeg(JNIEnv *env, jobject thiz) {

    av_register_all();
    AVCodec *c_temp = av_codec_next(NULL);
    while (c_temp != NULL) {
        switch (c_temp->type) {
            case AVMEDIA_TYPE_VIDEO:
                LOGD("[Video]:%s", c_temp->name);
                break;
            case AVMEDIA_TYPE_AUDIO:
                LOGD("[Audio]:%s", c_temp->name);
                break;
            default:
                LOGD("[Other]:%s", c_temp->name);
                break;
        }
        c_temp = c_temp->next;
    }

}

void *onPrepareCallback(void *data) {
    char *url = (char *) data;
    LOGD("onPrepareCallback");
    LOGD("open url:%s", url);
    if (getResult(url)) {
        JNIEnv *jniEnv;
        if (javaVm->AttachCurrentThread(&jniEnv, 0) != JNI_OK) {
            if (LOG_IS_DEBUG) {
                LOGE("c++创建线程失败");
            }
        } else {
            LOGD("c++调用java方法1");
            LOGD("jobj 地址:%#p", jobj);
            LOGD("jmethodId 地址:%#p", jmethodId);
            //c++调用java方法
            jniEnv->CallVoidMethod(jobj, jmethodId, urlStr);
            LOGD("c++调用java方法2");
        }
    }
    //退出当前线程
    pthread_exit(&decodeThread);
}

bool getResult(char *url) {
    LOGD("open url:%s", url);
    LOGD("getResult1");
    //1.注册解码器并初始化网络
    av_register_all();
    avformat_network_init();
    //2.打开文件或网络流
    avFormatContext = avformat_alloc_context();
    LOGD("getResult1.5");

    if (avformat_open_input(&avFormatContext, url, NULL, NULL) != 0) {
        //代表打开流错误
        if (LOG_IS_DEBUG) {
            LOGE("can not open url:%s", url);
        }
        return false;
    }
    LOGD("getResult2");
    //3.获取流信息
    if (avformat_find_stream_info(avFormatContext, NULL) < 0) {
        if (LOG_IS_DEBUG) {
            LOGE("获取流信息失败");
        }
        return false;
    }
    LOGD("getResult3");
    //4.获取音频流
    for (int i = 0; i < avFormatContext->nb_streams; i++) {
        LOGD("getResult3.5");
        if (avFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {//得到音频流
            LOGD("getResult3.6");
            if (myAudio == NULL) {
                myAudio = new MyAudio();
                myAudio->streamIndex = i;
                myAudio->codecParam = avFormatContext->streams[i]->codecpar;
            }
        }
    }
    LOGD("getResult4");
    //5.获取解码器
    AVCodec *avCodec = avcodec_find_decoder(myAudio->codecParam->codec_id);
    LOGD("getResult5");
    //6.利用解码器创建解码器上下文
    if (!avCodec) {
        if (LOG_IS_DEBUG) {
            LOGE("没有找到解码器");
        }
        return false;
    }
    myAudio->avCodecContext = avcodec_alloc_context3(avCodec);
    if (!myAudio->avCodecContext) {
        if (LOG_IS_DEBUG) {
            LOGE("创建解码器上下文失败");
        }
        return false;
    }
    LOGD("getResult6");
    //7.打开解码器
    if (avcodec_open2(myAudio->avCodecContext, avCodec, 0) !=
        0) {//zero on success, a negative value on error
        if (LOG_IS_DEBUG) {
            LOGE("打开解码器失败");
        }
        return false;
    }
    //8.读取音频帧
    LOGD("读取音频帧");
    return true;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_xiaokun_myplayer_Demo_n_1prepared(JNIEnv *env, jobject thiz, jstring source) {

    LOGD("jni ffmpeg 准备开始");

    const char *url = env->GetStringUTFChars(source, 0);

    urlStr = source;

    jclass clz = env->GetObjectClass(thiz);
    if (!clz) {
        if (LOG_IS_DEBUG) {
            LOGE("获取clz失败");
        }
        return;
    }

    jmethodId = env->GetMethodID(clz, "onCallPrepared", "()V");
    jniEnv = env;
    //创建一个全局引用
    jobj = env->NewGlobalRef(thiz);

    pthread_create(&decodeThread, NULL, onPrepareCallback, (void *) url);

    LOGD("测试线程时序");

    env->ReleaseStringUTFChars(source, url);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD("执行JNI_Onload1");
    JNIEnv *env;
    javaVm = vm;
    if (vm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    LOGD("执行JNI_Onload2");
    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_xiaokun_myplayer_Player_n_1prepared(JNIEnv *env, jobject thiz, jstring source) {
    LOGD("jni ffmpeg 准备开始");

    const char *url = env->GetStringUTFChars(source, 0);

    urlStr = source;

    jclass clz = env->GetObjectClass(thiz);
    if (!clz) {
        if (LOG_IS_DEBUG) {
            LOGE("获取clz失败");
        }
        return;
    }

    jmethodId = env->GetMethodID(clz, "onCallPrepared", "()V");
    jniEnv = env;
    //创建一个全局引用
    jobj = env->NewGlobalRef(thiz);

    pthread_create(&decodeThread, NULL, onPrepareCallback, (void *) url);

    LOGD("测试线程时序");

    env->ReleaseStringUTFChars(source, url);

}
extern "C"
JNIEXPORT void JNICALL
Java_com_xiaokun_myplayer_Player_n_1start(JNIEnv *env, jobject thiz) {

    if (myAudio == NULL) {
        LOGE("audio is null");
        return;
    }

    int count = 0;

    while (1) {
        AVPacket *avPacket = av_packet_alloc();
        //0 if OK, < 0 on error or end of file
        if (av_read_frame(avFormatContext, avPacket) == 0) {
            if (avPacket->stream_index == myAudio->streamIndex) {
                //解码+1
                count++;
                if (LOG_IS_DEBUG) {
                    LOGD("解码第 %d 帧", count);
                }
            }
            av_packet_free(&avPacket);
            av_free(avPacket);
        } else {
            if (LOG_IS_DEBUG) {
                LOGD("解码完成");
            }
            av_packet_free(&avPacket);
            av_free(avPacket);
            break;
        }
    }

}
