
#include "Detection.h"


//--------------------------------------------------------------
void Detection::setup()
{
    // Eventi customizzati del mouse/key che ascoltano gli eventi core di OF
    ofAddListener(ofEvents().keyPressed, this, &Detection::keyPressed);
    ofAddListener(ofEvents().keyReleased, this, &Detection::keyReleased);
    ofAddListener(ofEvents().mouseMoved, this, &Detection::mouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &Detection::mouseDragged);
    ofAddListener(ofEvents().mousePressed, this, &Detection::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &Detection::mouseReleased);
    
    bPressedInside = false;
    int w = 640; int h = 480;
    cam.initGrabber(w, h);
    colorImage.allocate(w, h);
    grayImage.allocate(w, h);
    
    confidenceMin = 70;
    cropRect.set(10, 10, w/2, h/2);
    
    templateDetected = false;
    
}

//--------------------------------------------------------------
void Detection::update(){
    
    
    cam.update();
    
    if(cam.isFrameNew())
    {
        colorImage.setFromPixels(cam.getPixels());
        grayImage = colorImage;
        
        //clear out all the old matches
        matches.clear();
        
        //look for any of the objects in the source image
        for (int i=0; i<objects.size(); i++)
        {
            int nFound = matcher.findMatches(grayImage, objects[i], confidenceMin);
            
            // copy over the matches and store the object id
            for (int j=0; j<matcher.matches.size(); j++)
            {
                matches.push_back(matcher.matches[j]);
                matches.back().objectID = i;
                
                cntMatch = matches[i].objectID;
            }
            
            printf("Found %i in object %i\n", nFound, i);
            engage = nFound;
            //cout << engage << endl;

        }
        
        
        
        
    }
    
}

//--------------------------------------------------------------
void Detection::detectItem(int _id)
{
    switch (_id)
    {
        case 0:
            ofPushStyle();
            ofSetColor(255, 0, 0);
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 300);
            ofPopStyle();
            break;
            
        case 1:
            ofPushStyle();
            ofSetColor(255, 255, 0);
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 300);
            ofPopStyle();
            break;
            
        case 2:
            ofPushStyle();
            ofSetColor(0, 0, 255);
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 300);
            ofPopStyle();
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void Detection::draw(){
    
    if(bDraw)
    {
        ofSetColor(255);
        grayImage.draw(10, 10);
        ofNoFill();
        ofSetHexColor(0xF5ECCF);
        ofDrawRectangle(cropRect);
        float ypos = 10;
        for(int i=0; i<objects.size(); i++)
        {
            ofPushMatrix();
            ofTranslate(ofGetWidth() - (objects[i].getWidth()+10), ypos);
            ofSetColor(255);
            objects[i].draw(0, 0);
            ofSetColor(255, 255, 0);
            ofDrawBitmapString(ofToString(i), 0, 15);
            detectItem(i);
            for(int j=0; j<objects[i].pts.size(); j++)
            {
                ofSetHexColor(0xF5ECCF);
                ofDrawCircle(objects[i].pts[j], 20);
            }
            ofPopMatrix();
            ypos += objects[i].getHeight()+10;
        }
        
        ofPushMatrix();
        ofTranslate(20 + cam.getWidth(), 10);
        ofSetColor(255);
        grayImage.draw(0, 0);
        
        for (int i=0; i<matches.size(); i++)
        {
            matches[i].draw();
            
            detectItem( matches[i].objectID);
        }
        ofPopMatrix();
        
        ofSetHexColor(0xF5ECCF);
        ofDrawBitmapString("Draw a bounding box around object\nPress spacebar to capture object\nUp/Down to change confidence threshold\nFPS: "+ofToString(ofGetFrameRate(),0)+"\nConfidence Min:"+ofToString(confidenceMin)+"%", 10, cam.getHeight()+30);
        
        
    }
    
}

//--------------------------------------------------------------
void Detection::keyPressed(ofKeyEventArgs & key)
{
    if(key.key == ' ')
    {
        objects.push_back(MatchObject());
        objects.back().allocate(cropRect.width, cropRect.height);
        grayImage.setROI(cropRect.x-10, cropRect.y-10, cropRect.width, cropRect.height);
        objects.back().setFromPixels(grayImage.getRoiPixels().getPixels(), cropRect.width, cropRect.height);
        grayImage.resetROI();
    }
    if(key.key == 'c')
    {
        objects.clear();
    }
    if(key.key == OF_KEY_UP)
    {
        if(confidenceMin<100) confidenceMin ++;
    }
    if(key.key == OF_KEY_DOWN)
    {
        if(confidenceMin>0) confidenceMin --;
    }
    if(key.key == 'h')
    {
        bDraw = !bDraw;
    }
}

//--------------------------------------------------------------
void Detection::keyReleased(ofKeyEventArgs & key){
    
}

//--------------------------------------------------------------
void Detection::mouseMoved(ofMouseEventArgs & mouse){
    
}

//--------------------------------------------------------------
void Detection::mouseDragged(ofMouseEventArgs & mouse)
{
    if(bPressedInside)
    {
        if(mouse.x > downPos.x+5 && mouse.y > downPos.y+5)
        {
            cropRect.width  = mouse.x - downPos.x;
            cropRect.height = mouse.y - downPos.y;
            if(cropRect.height+cropRect.y>cam.getHeight()) cropRect.height = (cam.getHeight()-cropRect.y)+10;
            if(cropRect.width+cropRect.x>cam.getWidth()) cropRect.width = (cam.getWidth()-cropRect.x)+10;
        }
    }
}

//--------------------------------------------------------------
void Detection::mousePressed(ofMouseEventArgs & mouse)
{
    if(ofRectangle(10, 10, cam.getWidth(), cam.getHeight()).inside(mouse.x, mouse.y))
    {
        cropRect.setPosition(mouse.x, mouse.y);
        if(cropRect.width+cropRect.x>cam.getWidth()) cropRect.width = (cam.getWidth()-mouse.x)+10;
        if(cropRect.height+cropRect.y>cam.getHeight()) cropRect.height = (cam.getHeight()-mouse.y)+10;
        downPos.set(mouse.x, mouse.y);
        bPressedInside = true;
    }
}

//--------------------------------------------------------------
void Detection::mouseReleased(ofMouseEventArgs & mouse)
{
    bPressedInside = false;
}


