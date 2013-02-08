#include "testApp.h"
/*
cam res 656 x 492
*/
//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(0);
    ofSetFrameRate(66);

    bCameraFound = false;
    bCamInit = false;
    bGrabbing = false;

    thread.startThread(true, false);
    camImage.allocate(656, 492, OF_IMAGE_GRAYSCALE);
    grayCam.allocate(656, 492);
    bgImage.allocate(656, 492);
    diffImage.allocate(656, 492);

    bCamInit = true;
    doTrack = false;
    doBg = true;

    thresh = 40;
}


void testApp::update(){

    thread.lock();
        camImage = thread.mantaImage;
        grayCam.setFromPixels(camImage.getPixels(), 656, 492);

    thread.unlock();


        if(doBg){
            bgImage = grayCam;
            doBg = false;
        }


            diffImage.absDiff(bgImage, grayCam);
            diffImage.threshold(thresh);


        finder.findContours(diffImage, 10, (656*492)/3, 1, true, false);

}

//--------------------------------------------------------------
void testApp::exit(){
    thread.stopThread();
}
//--------------------------------------------------------------
void testApp::draw(){
    diffImage.draw(0, 0);
    finder.draw(0, 0);

    ofPushMatrix();
        ofSetColor(0, 255, 0);
        ofDrawBitmapString("fRate: "+ofToString(ofGetFrameRate())+" "+"thresh: "+ofToString(thresh), 10, 470);
        ofSetColor(255, 255, 255);
    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    switch(key){

        case('a'):
            thresh++;
        break;
        case('q'):
            if(thresh > 0){
                thresh -= 1;
            }
        break;
        case(' '):
            doBg = true;

        break;
        case('t'):
            doTrack = true;
        break;
        }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
