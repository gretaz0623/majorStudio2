#pragma once

#include "ofMain.h"
#include "ofxGif.h"
#include "particles.hpp"
#define NSMOG0 1000

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
    
        snow mySnow[NSMOG0];
    
        ofArduino	ard;
        bool		bSetupArduino;// flag variable for setting up arduino once

    
        string songName[3];
        string num[3];
    
        ofxGIF::fiGifLoader gifloader;
        int index = 10;
        float gifDelay = 100;
        float startTime;
    
  
    
//        ofxGIF::fiGifLoader gifloader01;
//        int index01 = ofRandom(0,4);
//        float gifDelay01 = 100;
//        float startTime01;
//    

    
    private:
    
        void setupArduino(const int & version);
        void updateArduino();
    
		
};
