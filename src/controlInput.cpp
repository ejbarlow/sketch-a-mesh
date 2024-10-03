//
//  controlInput.cpp
//  sketchamesh-beta
//
//  Created by ed on 14/03/2023.
//

#include "controlInput.hpp"

// common type for input values, is returned from
// gui or gpio control classes
ControlInput::ControlInput() {
    
}

ofPoint ControlInput::getRelativePosition() {
    ofPoint absolutePosition(x, y, z);
    return absToRel(absolutePosition);
}

ofPoint ControlInput::getAbsolutePosition() {
    return ofPoint(x, y, z);
}

ofPoint ControlInput::absToRel(ofPoint p) {
    ofPoint relativePosition = p.getRotated(-rx, ofVec3f(1, 0, 0));
    relativePosition = relativePosition.getRotated(-ry, ofVec3f(0, 1, 0));
    relativePosition = relativePosition.getRotated(-rz, ofVec3f(0, 0, 1));
    return relativePosition;
}

ofPoint ControlInput::relToAbs(ofPoint p) {
    ofPoint absolutePosition = p.getRotated(rz, ofVec3f(0, 0, 1));
    absolutePosition = absolutePosition.getRotated(ry, ofVec3f(0, 1, 0));
    absolutePosition = absolutePosition.getRotated(rx, ofVec3f(1, 0, 0));
    return absolutePosition;
}
