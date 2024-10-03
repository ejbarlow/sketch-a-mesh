//
//  controlInput.hpp
//  sketchamesh-beta
//
//  Created by ed on 14/03/2023.
//

#ifndef controlInput_hpp
#define controlInput_hpp

#include <stdio.h>
#include "ofMain.h"

class ControlInput {
public:
    bool toggle;
    int x;
    int y;
    int z;
    int rx;
    int ry;
    int rz;
    ControlInput();
    
    ofPoint getRelativePosition();
    ofPoint getAbsolutePosition();
    ofPoint absToRel(ofPoint p);
    ofPoint relToAbs(ofPoint p);
};

#endif /* controlInput_hpp */
