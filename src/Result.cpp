#include "Result.h"

Result::Result()
{
    
}

void Result::setup()
{
    result.load("pictures/result.png");
    result.resize(ofGetWidth(), ofGetHeight());
}

void Result::update()
{
    result.resize(ofGetWidth(), ofGetHeight());
}

void Result::draw()
{
    result.draw(0,0);
}

