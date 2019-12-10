//
// Created by 83849 on 2019/12/8.
//

#ifndef MY_APPLICATION_MYAUDIO_H
#define MY_APPLICATION_MYAUDIO_H


#include "PlayStatus.h"
#include "Queue.h"

extern "C" {
#include "include/libavcodec/avcodec.h"
}

class MyAudio {

public:
    int streamIndex = -1;
    AVCodecContext *avCodecContext;
    AVCodecParameters *codecParam;

    PlayStatus *playStatus = NULL;
    Queue *queue = NULL;
public:
    MyAudio(PlayStatus *status);

    ~MyAudio();
};


#endif //MY_APPLICATION_MYAUDIO_H
