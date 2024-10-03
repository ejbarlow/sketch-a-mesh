//
//  gpioControl.hpp
//  sketchamesh-beta
//
//  Created by ed on 14/03/2023.
//

#ifndef gpioControl_hpp
#define gpioControl_hpp

#define BUFF_SIZE 16

#include <stdio.h>
#include "ofxGPIO.h"
#include "controlInput.hpp"

class GpioControl {
    ControlInput input;
    
public:
    GpioControl();
    
    MCP mcp;
    
    int toggleBuff[BUFF_SIZE];
    int xBuff[BUFF_SIZE];
    int yBuff[BUFF_SIZE];
    int zBuff[BUFF_SIZE];
    int rxBuff[BUFF_SIZE];
    int ryBuff[BUFF_SIZE];
    int rzBuff[BUFF_SIZE];
    int bufferIndex;
    
    ControlInput getInput();
    int average(int buff[BUFF_SIZE]);
};

#endif /* gpioControl_hpp */
