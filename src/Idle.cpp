#include "Idle.h"

Idle::Idle()
{
    
}

void Idle::setup()
{
    IdleVideo.load("movies/video.mov");
    IdleVideo.play();
}

void Idle::update()
{
    IdleVideo.update(); // get all the new frames
}

void Idle::draw()
{
    IdleVideo.draw(0,0); // draw at 20, 20 from the current transform matrix
}

