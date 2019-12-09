//
// Created by 83849 on 2019/12/8.
//

#ifndef MY_APPLICATION_MYAUDIO_H
#define MY_APPLICATION_MYAUDIO_H


extern "C" {
#include "include/libavcodec/avcodec.h"
}

class MyAudio {

public:
    int streamIndex = -1;
    AVCodecContext *avCodecContext;
    AVCodecParameters *codecParam;

public:
    MyAudio();

    ~MyAudio();
};


#endif //MY_APPLICATION_MYAUDIO_H
