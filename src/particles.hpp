//
//  particles.hpp
//  Major Studio Final
//
//  Created by Zhao Hanyu on 10/05/2017.
//
//

#ifndef particles_hpp
#define particles_hpp

#include <stdio.h>
#include "ofMain.h"

class snow{
    
public:
    
    //    void setup();
    void update();
    void draw();
    
    void setup();
    
    float x;
    float y;
    float speedY;
    float speedX;
    float dim;
    ofColor color;
    snow();
    
private:
    
    
    
};



#endif /* particles_hpp */
