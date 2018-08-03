#include "Call.h"

Call::Call()
{
    
}

void Call::setup()
{
    video.load("pictures/callvideo.mov");
    video.setLoopState(OF_LOOP_NONE);
    
    cout << "********INIZIO VIDEO********" << endl;
  
}

void Call::play()
{
    video.play();
}

void Call::stop()
{
    video.stop();
}

void Call::update()
{
    //cout << "********show video********" << endl;
    video.update();
}

void Call::draw()
{
    video.draw(0,0);
}

bool Call::isMovieDone()
{
    if(video.getIsMovieDone())
    {
        return true;
        cout << "video.getIsMovieDone()" << endl;
    }
    else
    {
        return false;
    }
}

bool Call::isPlaying()
{
    if(video.isPlaying())
    {
        return  true;
    }
    else
    {
        return false;
    }
}












