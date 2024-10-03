//
//  guiControl.hpp
//  sketchamesh-beta
//
//  Created by ed on 14/03/2023.
//

#ifndef guiControl_hpp
#define guiControl_hpp

#include <stdio.h>
#include "ofxGui.h"
#include "controlInput.hpp"

class GuiControl {
    ofxPanel panel;
    ControlInput input;
public:
    ofParameter<bool> toggle;
    ofParameter<int> x;
    ofParameter<int> y;
    ofParameter<int> z;
    ofParameter<int> rx;
    ofParameter<int> ry;
    ofParameter<int> rz;
    GuiControl();
    
    void draw();
    ControlInput getInput();
};

#endif /* guiControl_hpp */
