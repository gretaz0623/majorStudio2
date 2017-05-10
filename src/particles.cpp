//
//  particles.cpp
//  Major Studio Final
//
//  Created by Zhao Hanyu on 10/05/2017.
//
//

#include "particles.hpp"

snow::snow(){
    
}

void snow::setup(){
    
    dim = ofRandom(0.5,3);
    
    x = ofRandom(ofRandom(ofGetWidth()/2-5,ofGetWidth()/2+5));
    y = ofRandom(ofRandom(ofGetHeight()/2 -5,ofGetHeight()/2 +5));
    
    speedX = ofRandom(-10.0f,10.0f);
    speedY = ofRandom(-10.0f,10.0f);
    
    color.set(13,100,239);
 
    
    
}

void snow::update(){
    
    
    if(x<0){
        x = 0;
        speedX *= -1;
    } else if (x > ofGetWidth()){
        x = ofGetWidth();
        speedX *= -1;
        
        
    }
    
    if (y < 0) {
        y = 0;
        speedY += -1;
    } else if (y  > ofGetHeight()){
        y = ofGetHeight();
        speedY *= -1;
    }
    
    x += speedX;
    y += speedY;
    
    
}

void snow::draw(){
    
    
    
    ofSetColor(color,ofRandom(200,230));
    ofDrawCircle(x,y,dim);

    
    
    
    
    
}
