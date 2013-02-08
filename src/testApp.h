#pragma once

#define _LINUX
#define _x86
#define MAX_CAM 1
#define WIDTH 656
#define HEIGHT 492

#include "ofMain.h"
#include "mantaThread.h"
#include "ofxOpenCv.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        bool bCameraFound, bCamInit, bGrabbing, doBg, doTrack;

        mantaThread thread;

        ofImage camImage;
        ofxCvGrayscaleImage bgImage, grayCam, diffImage;


        int thresh;
        ofxCvContourFinder finder;
};
