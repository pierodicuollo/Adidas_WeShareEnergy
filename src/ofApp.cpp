#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetBackgroundColor(0);
    ofSetCircleResolution(360);
    
    idle = new Idle();
    idle->setup();
    
    detect = new Detection();
    detect->setup();
    
    call = new Call();
    call->setup();
    
    result = new Result();
    result->setup();
    
    play = new Play();
    play->setup();
    play->setupGui();
    
    mode = IDLE;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    setState(mode);
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 20, 20);
}

void ofApp::setState(StateMode m)
{
    switch (m)
    {
        case IDLE:
            call->stop();
            detect->update();
            detect->draw();
            
            idle->update();
            idle->draw();
            //cout << " IDLE " << endl;
            if(detect->engage == 1)
            {
                mode = CREATE_ENERGY;
            }
                
            break;
            
        case ENGAGEMENT:
            
            detect->update();
            detect->draw();
            //cout << " ENGAGEMENT " << endl;

            break;
            
        case CREATE_ENERGY:

            call->update();
            call->draw();
            //cout << " CREATE_ENERGY " << endl;

            
            // se il video ha finito
            if(call->isMovieDone())
            {
                mode = GAME;
            }
            else // video è false
            {
                if(!call->isPlaying())
                    call->play();
            }
            
            break;
            
        case GAME:
            call->stop();
            play->update();
            play->draw();
            
            break;
            
        case RESULT:
            result->update();
            result->draw();
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    switch (key)
    {
        case 'i':
        case 'I':
            mode = IDLE;
            break;
            
        case 'd':
        case 'D':
            mode = ENGAGEMENT;
            break;
            
        case 'e':
        case 'E':
            mode = CREATE_ENERGY; // gestita nell'update!
            call->play(); // una volta sola fai il play!!!
            break;
            
        case 'p':
        case 'P':
            mode = GAME;
            break;
            
        case 'k':
            mode = RESULT;
            break;
            
        case 's':
            img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
            img.save("screen_" + ofGetTimestampString() + ".png");
            break;
            
        default:
            break;
    }

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
