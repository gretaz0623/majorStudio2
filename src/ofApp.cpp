#include "ofApp.h"
unsigned long lastMillis;
float RV_Wind_ADunits;
float RV_Wind_Volts;
const float zeroWindAdjustment =  .2;
int TMP_Therm_ADunits;

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetFrameRate(120.0f);
    ofBackground(32,38,38);
    ofSetCircleResolution(60);
    
    music.load("ding.mp3");




    
   
    ard.connect("/dev/cu.usbmodem1411", 57600);
    
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);


    bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
//tty.HC-05-DevB
}

//--------------------------------------------------------------
void ofApp::update(){
    updateArduino();

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
//--------------------------------------------------------------
void ofApp::draw(){
    RV_Wind_ADunits = ard.getAnalog(1);
    TMP_Therm_ADunits = ard.getAnalog(0);
//    cout <<   RV_Wind_ADunits << endl;
//    cout <<   ard.getAnalog(1) << endl;
//    cout <<   ard.getAnalog(0) << endl;
//
//    

   
//if(ofGetElapsedTimef()- lastMillis >200 ){
        RV_Wind_ADunits = ard.getAnalog(1);
        RV_Wind_Volts = RV_Wind_ADunits *  0.0048828125;
        float zeroWind_ADunits = -0.0006*((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits) + 1.0727 * (float)TMP_Therm_ADunits + 47.172;
        float zeroWind_volts = (zeroWind_ADunits * 0.0048828125) - zeroWindAdjustment;
        float WindSpeed_MPH =  pow(((RV_Wind_Volts - zeroWind_volts) /.2300) , 2.7265);
        
        speed = ofMap((float)WindSpeed_MPH, 0,3,0,255);
        
        cout << speed << endl;
        lastMillis = ofGetElapsedTimef();

    
            //
    if(speed >120){
        music.play();
        ofSetColor(32,38,38,20);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
        ofSetBackgroundColor(32,38,38);
        ofSetColor(237,182,25);
        ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, speed/2);
        
        
    }else{
//        music.stop();
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


