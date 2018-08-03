#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxTemplateMatching.h"
#include "Idle.h"
#include "Result.h"
#include "Call.h"
#include "Detection.h"
#include "ofxXmlSettings.h"
#include "ofxGui.h"
#include "ofxFlowTools.h"
#include "Play.h"
#include "ofFbo.h"


using namespace flowTools;

enum StateMode
{
    IDLE,
    ENGAGEMENT, //detection
    CREATE_ENERGY, //text placeholder you are wearing clean energy
    GAME,
    RESULT //IMAGE PLACEHOLDER CHECK RESULT
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    bool bEnd = false;
    
    //STATEMACHINE
    Idle *idle;
    Detection *detect;
    Call *call;
    Play *play;
    Result *result;
    StateMode mode;
    void setState(StateMode m);
    
    ofImage   img;
		
};
