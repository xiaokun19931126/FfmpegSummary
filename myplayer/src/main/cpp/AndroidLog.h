//
// Created by 83849 on 2019/12/2.
//

#ifndef JNITHREAD_ANDROIDLOG_H
#define JNITHREAD_ANDROIDLOG_H

#endif //JNITHREAD_ANDROIDLOG_H

#include "android/log.h"
#define LOG_IS_DEBUG true
#define LOGD(FORMAT,...) __android_log_print(ANDROID_LOG_DEBUG,"xiaokun",FORMAT,##__VA_ARGS__)
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"xiaokun",FORMAT,##__VA_ARGS__)