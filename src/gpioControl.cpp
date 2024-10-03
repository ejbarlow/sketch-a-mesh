//
//  gpioControl.cpp
//  sketchamesh-beta
//
//  Created by ed on 14/03/2023.
//

#include "gpioControl.hpp"
#include "controlInput.hpp"

GpioControl::GpioControl() {
    // MCP3008 analog to digital integrated circuit for
    // getting analog input values from variable resistors
    MCP_DESC chip = MCP3008;
    // set up SPI communication
    mcp.setup("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
    bufferIndex = 0;
    
    int halfW = ofGetWidth() / 2;
    int halfH = ofGetHeight() / 2;
    
    // signals are smoothed by taking a running average of input values
    for (int i = 0; i < BUFF_SIZE; i++) {
        xBuff[i] = ofMap(mcp.getValueChannel(0), 0, 1024, halfW, -halfW);
        yBuff[i] = ofMap(mcp.getValueChannel(1), 0, 1024, -halfH, halfH);
        zBuff[i] = ofMap(mcp.getValueChannel(2), 0, 1024, -400, 400);
        rxBuff[i] = ofMap(mcp.getValueChannel(4), 0, 1024, -180, 180);
        ryBuff[i] = ofMap(mcp.getValueChannel(3), 0, 1024, 180, -180);
        rzBuff[i] = ofMap(mcp.getValueChannel(5), 0, 1024, -180, 180);
        toggleBuff[i] = ofMap(mcp.getValueChannel(6), 0, 1024, 0, 1);
    }
}

ControlInput GpioControl::getInput() {
    int halfW = ofGetWidth() / 2;
    int halfH = ofGetHeight() / 2;
    xBuff[bufferIndex] = ofMap(mcp.getValueChannel(0), 0, 1024, halfW, -halfW);
    yBuff[bufferIndex] = ofMap(mcp.getValueChannel(1), 0, 1024, -halfH, halfH);
    zBuff[bufferIndex] = ofMap(mcp.getValueChannel(2), 0, 1024, -400, 400);
    // snap rotations to neutral if within 10 degrees
    int rxVal = ofMap(mcp.getValueChannel(4), 0, 1024, -180, 180);
    if (rxVal > -10 && rxVal < 10) {
        rxVal = 0;
    }
    rxBuff[bufferIndex] = rxVal;
    int ryVal = ofMap(mcp.getValueChannel(3), 0, 1024, 180, -180);
    if (ryVal > -10 && ryVal < 10) {
        ryVal = 0;
    }
    ryBuff[bufferIndex] = ryVal;
    int rzVal = ofMap(mcp.getValueChannel(5), 0, 1024, -180, 180);
    if (rzVal > -10 && rzVal < 10) {
        rzVal = 0;
    }
    rzBuff[bufferIndex] = rzVal;
    toggleBuff[bufferIndex] = ofMap(mcp.getValueChannel(6), 0, 1024, 0, 1024);
    bufferIndex++;
    if (bufferIndex > BUFF_SIZE - 1) {
        bufferIndex = 0;
    }
    
    input.x = average(xBuff);
    input.y = average(yBuff);
    input.z = average(zBuff);
    input.rx = average(rxBuff);
    input.ry = average(ryBuff);
    input.rz = average(rzBuff);
    input.toggle = average(toggleBuff);
    
    return input;
}

int GpioControl::average(int buff[BUFF_SIZE]) {
    int sum = 0;
    for (int i = 0; i < BUFF_SIZE; i++) {
        sum += buff[i];
    }
    return (int) sum / BUFF_SIZE;
}
