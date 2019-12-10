//
// Created by 83849 on 2019/12/10.
//

#ifndef MY_APPLICATION_QUEUE_H
#define MY_APPLICATION_QUEUE_H

#include "queue"
#include "PlayStatus.h"

extern "C" {
#include "libavcodec/avcodec.h"
};

class Queue {
public:
    std::queue<AVPacket *> queuePacket;
    pthread_mutex_t mutexPacket;
    pthread_cond_t pthreadCond;
    PlayStatus *playStatus = NULL;

public:
    Queue(PlayStatus *playStatus);

    //入队
    int putAvPacket(AVPacket *avPacket);

    //出队
    int getAvPacket(AVPacket *avPacket);

    //获取队列size
    int getQueueSize();

    ~Queue();
};


#endif //MY_APPLICATION_QUEUE_H
