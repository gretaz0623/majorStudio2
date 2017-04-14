#pragma once

#include "ofMain.h"

#define blue 56 90 209
#define yellow 237 182 25
#define purple 208 198 233
#define red 240 68 37
#define bg 32 38 38

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
    
        ofArduino	ard;
        bool		bSetupArduino;// flag variable for setting up arduino once
        ofSoundPlayer music;
    
    private:
    
        void setupArduino(const int & version);
        void updateArduino();
		
};
