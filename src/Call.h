#pragma once

#include "ofMain.h"

class Call
{
    
public:
    
    Call();
    void setup();
    void update();
    void draw();
    void play();
    void stop();
    
    bool isMovieDone();
    bool isPlaying();
    
    ofVideoPlayer video;
};

