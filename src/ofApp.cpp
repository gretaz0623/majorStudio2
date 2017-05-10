#include "ofApp.h"
unsigned long lastMillis;
float RV_Wind_ADunits;
float RV_Wind_Volts;
const float zeroWindAdjustment =  .2;
int TMP_Therm_ADunits;

float* fftSmoothed;
ofSoundPlayer sound;
ofFbo fbo;
const int numBands = 512;
float spectrum[numBands];
float count1;
int Num = 1;

//--------------------------------------------------------------
void ofApp::setup(){
    CGDisplayHideCursor(NULL); // <- OK
//    ofSetFullscreen(true);

    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F);
    ofSetBackgroundColor(32, 38, 38);
    

    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetFrameRate(120.0f);
    ofBackground(32,38,38);
    ofSetCircleResolution(60);
    //
    
    
    for(int i = 0; i < 3; i++){
        
        num[i] = ofToString(i);
        songName[i] = num[i] + ".mp3";
        
    }
    
    

   sound.load(songName[1]);
    //sound.load("2.mp3");
    sound.setVolume(0.6);
//    sound2.load("2.mp3");
//    sound3.load("3.mp3");
    
    for (int i = 0; i < numBands; i++) {
        spectrum[i] = 0.0f;
    }
    
    gifloader.load("06.gif");
    startTime = ofGetElapsedTimeMillis();
    
//    gifloader01.load("07.gif");
//    startTime01 = ofGetElapsedTimeMillis();
   
ard.connect("/dev/cu.HC-05-DevB-1", 9600);
   // "/dev/cu.HC-05-DevB"
  //  ard.connect("/dev/cu.usbmodem1411", 57600);
    
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);


    bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
    
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();

}

//--------------------------------------------------------------
void ofApp::update(){

    if (Num > 0){ Num = ofRandom(0,3);}
   
    if (ofGetElapsedTimeMillis() - startTime >= gifDelay) {
        index++;
        if (index > gifloader.pages.size() - 1) {
            index = 0;
        }
        startTime = ofGetElapsedTimeMillis();
    }
    
//    if (ofGetElapsedTimeMillis() - startTime01 >= gifDelay01) {
//        index01++;
//        if (index01 > gifloader01.pages.size() - 1) {
//            index01 = 0;
//        }
//        startTime01 = ofGetElapsedTimeMillis();
//    }
    
    updateArduino();
    
    float *val = ofSoundGetSpectrum(numBands);

    count1 += spectrum[1];
    
    for (int i = 0; i < numBands; i++) {
        spectrum[i] *= 0.95;
        spectrum[i] = max(spectrum[i] * ofRandom(0.02, 0.05), val[i]);
    }


}

void ofApp::setupArduino(const int & version) {
    
	ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
   
    bSetupArduino = true;
    
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    //a0 a1 pin set
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    ard.sendAnalogPinReporting(1, ARD_ANALOG);
    
    
    ard.sendDigitalPinMode(2, ARD_INPUT);
    ard.sendDigitalPinMode(3, ARD_INPUT);
//    ard.sendDigitalPinMode(3, ARD_LOW);
    

}

void ofApp::updateArduino(){

    ard.update();
    
   }
//potValue = "analog pin: " + ofToString(pinNum) + " = " + ofToString(ard.getAnalog(pinNum));
int speed;
float rX = 0;
float rY = 0;
float rZ = 0;
float a = ofRandom(0,5);
float x,y,z;
float sTime = ofGetElapsedTimef();
//--------------------------------------------------------------
void ofApp::draw(){
    RV_Wind_ADunits = ard.getAnalog(1);
    TMP_Therm_ADunits = ard.getAnalog(0);
    RV_Wind_ADunits = ard.getAnalog(1);
    
    RV_Wind_Volts = RV_Wind_ADunits *  0.0048828125;
    float zeroWind_ADunits = -0.0006*((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits) + 1.0727 * (float)TMP_Therm_ADunits + 47.172;
    float zeroWind_volts = (zeroWind_ADunits * 0.0048828125) - zeroWindAdjustment;
    float WindSpeed_MPH =  pow(((RV_Wind_Volts - zeroWind_volts) /.2300) , 2.7265);
        
    speed = ofMap((float)WindSpeed_MPH, 0,3,0,255);
        
        cout << speed << endl;
        lastMillis = ofGetElapsedTimef();


    if(speed >20){
        
        fbo.begin();
        ofPushStyle();
        ofSetColor(0,0,0,1);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
        ofPopStyle();
        
        ofPushMatrix();
      
        ofSetColor(32,38,38,20);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
        
        ofSetColor(237,182,25);
        ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, speed*3);
        
        //sound.play();
        for(int i = 0; i < 3; i++){
            
            num[i] = ofToString(i);
            songName[i] = num[i] + ".mp3";
            Num ++;
            
        }
        
        cout<<"Num: "<<Num<<endl;
        sound.load(songName[Num]+".mp3");
        sound.play();

    
        ofPopMatrix();
        
        fbo.end();
        
        fbo.draw(0,0);
        
        ofSetColor(255, 255, 255, 255);
        ofImage img = gifloader.pages[index];
        ofPixels pix = img.getPixels();
        img.setFromPixels(pix);
        float i = img.getWidth();
        float j = img.getHeight();
        img.draw(ofGetWidth()/2 - i/2,ofGetHeight()/2-j/2);
       
        
//        
//        ofSetColor(255, 255, 255, 255);
//        ofImage img01 = gifloader01.pages[index01];
//        ofPixels pix01 = img01.getPixels();
//        img01.setFromPixels(pix01);
//        float q = img01.getWidth();
//        float w = img01.getHeight();
//        img01.draw((ofGetWidth()/2 - q/2)-200,(ofGetHeight()/2-w/2)-200);
        
    }
    
    
//    if(speed >100){
//        ofSetColor(0,182,25);
//        ofDrawCircle(ofGetWidth()/2 + 100, ofGetHeight()/2, speed/3);
//    }

    if(speed != -2147483648 && speed > 0){
        

    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotate(count1);
    
    float radius = 90;
    for (int i = 0; i < numBands; i++) {
        float x = radius * cos(ofDegToRad(i));
        float y = radius * sin(ofDegToRad(i));
        float size = spectrum[i] * ofRandom(100, 200);
        size *= ofRandom(-1, 1);
        
        int c = ofRandom(30,80);
        ofSetColor(c, 90, 209);
        ofDrawCircle(x, y, size);
    }
    
    float radius2 = 360;
    for (int i = 0; i < numBands; i += 2) {
        float time = sTime * a + ofGetElapsedTimef();
        rX = ofSignedNoise(time * 0.1) * radius2;
        rY = ofSignedNoise(time * 0.1) * radius2;
        rZ = ofSignedNoise(time * 0.1) * radius2;
        
        x = ofSignedNoise(time * 0.2) *spectrum[i];
        y = ofSignedNoise(time * 0.4) *spectrum[i];
        z = ofSignedNoise(time * 0.6) *spectrum[i];
        
        float a = radius2 * sin(ofDegToRad(i)) +  spectrum[i] * ofRandom(300, 400);
        float b = radius2 * cos(ofDegToRad(i)) +  spectrum[i] * ofRandom(300, 400);
        float a2 = radius2 * sin(ofDegToRad(i));
        float b2 = radius2 * cos(ofDegToRad(i));
        
        float x = radius2 * sin(ofDegToRad(i * 0.8)) + 100;
        float y = radius2 * cos(ofDegToRad(i * 0.8)) + 100;
        float size = spectrum[i] * ofRandom(300, 400);
        size *= ofRandom(-1, 1);
        
//      ofTranslate(x,y,z);
        ofScale(1,1,1);
        ofRotateX(rX);
        ofRotateY(rY);
        ofRotateZ(rZ);
        int c = ofRandom(40,100);
        ofSetColor(240, c, 37);
 
        ofDrawLine(a,b,a2,b2);
        ofDrawRectangle(x, y, size, size);
    }
    
    
    float radius3 = speed*2;
    for (int i = 0; i < numBands; i++) {
        float x = radius3 * sin(ofDegToRad(i)) +  spectrum[i];
        float y = radius3 * cos(ofDegToRad(i)) +  spectrum[i];
        float x2 = radius3 * sin(ofDegToRad(i))* ofRandom(1, 3);
        float y2 = radius3 * cos(ofDegToRad(i))* ofRandom(1, 3);
//
        
   
        ofSetColor(208, 198, 233,ofRandom(30,40));
        ofDrawLine(x, y, x2, y2);
        ofSetColor(255);
        ofDrawRectangle((x2-x)+3,(y2-y)+3,speed/100, speed/100);
        
    
//
        
    }
}



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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


