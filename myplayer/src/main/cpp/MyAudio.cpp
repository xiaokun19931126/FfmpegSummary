//
// Created by 83849 on 2019/12/8.
//

#include "MyAudio.h"

MyAudio::MyAudio(PlayStatus *status) {
    this->playStatus = status;
    this->queue = new Queue(playStatus);
}

MyAudio::~MyAudio() {

}
