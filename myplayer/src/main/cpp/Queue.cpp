//
// Created by 83849 on 2019/12/10.
//

#include "Queue.h"
#include "pthread.h"
#include "AndroidLog.h"

Queue::Queue(PlayStatus *playStatus) {
    this->playStatus = playStatus;
    pthread_mutex_init(&mutexPacket, NULL);
    pthread_cond_init(&pthreadCond, NULL);
}

Queue::~Queue() {
    pthread_cond_destroy(&pthreadCond);
    pthread_mutex_destroy(&mutexPacket);
}

/**
 * 将avPacket指针传入队列中
 */
int Queue::putAvPacket(AVPacket *avPacket) {

    pthread_mutex_lock(&mutexPacket);

    queuePacket.push(avPacket);
    if (LOG_IS_DEBUG) {
        LOGD("入队一个AVPacket，个数为：%d", queuePacket.size());
    }

    pthread_cond_signal(&pthreadCond);
    pthread_mutex_unlock(&mutexPacket);
    return 0;
}

/**
 * 出队列
 * @param avPacket
 * @return
 */
int Queue::getAvPacket(AVPacket *avPacket) {
    pthread_mutex_lock(&mutexPacket);

    LOGD("playStatus 指针：%p", playStatus);
    //LOGD("queuePacket 指针：%p", queuePacket);

    while (playStatus != NULL && !playStatus->exit) {
        LOGD("getAvPacket1");
        if (queuePacket.size() > 0) {
            LOGD("getAvPacket2");
            //获取队列头
            AVPacket *packet = queuePacket.front();
            LOGD("getAvPacket3");
            if (av_packet_ref(avPacket, packet) == 0) {//复制成功
                LOGD("getAvPacket4");
                //出队列
                queuePacket.pop();
            }
            LOGD("getAvPacket5");
            av_packet_free(&packet);
            LOGD("getAvPacket6");
            av_free(packet);
            packet = NULL;
            LOGD("getAvPacket7");
            if (LOG_IS_DEBUG) {
                LOGD("从队列中取出一个avpacket,还剩下 %d 个", queuePacket.size());
            }
            break;
        } else {
            //如果队列中没有数据,等待中
            pthread_cond_wait(&pthreadCond, &mutexPacket);
        }
    }

    pthread_mutex_unlock(&mutexPacket);
    return 0;
}

int Queue::getQueueSize() {
    int size = 0;
    pthread_mutex_lock(&mutexPacket);
    size = queuePacket.size();
    pthread_mutex_unlock(&mutexPacket);
    return size;
}
