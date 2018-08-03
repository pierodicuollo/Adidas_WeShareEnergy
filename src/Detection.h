#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxTemplateMatching.h"

class Detection
{
    
public:
    
    void setup();
    void update();
    void draw();
    void detectItem(int _id);
    
    void keyPressed(ofKeyEventArgs & key);
    void keyReleased(ofKeyEventArgs & key);
    
    void mouseMoved(ofMouseEventArgs & mouse);
    void mouseDragged(ofMouseEventArgs & mouse);
    void mousePressed(ofMouseEventArgs & mouse);
    void mouseReleased(ofMouseEventArgs & mouse);
    
    ofxTemplateMatching matcher;
    vector <MatchObject> objects;
    vector <TemplateMatch> matches;
    
    ofVideoGrabber cam;
    ofxCvColorImage colorImage;
    ofxCvGrayscaleImage grayImage;
    ofRectangle cropRect;
    ofPoint downPos;
    
    bool bPressedInside;
    int confidenceMin;
    bool templateDetected;
    bool bDraw;
    int cntMatch;
    int engage;
};


