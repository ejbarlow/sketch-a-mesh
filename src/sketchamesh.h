#pragma once

#include "ofMain.h"

#if TARGET == 0
#include "guiControl.hpp"
#elif TARGET == 1
#include "gpioControl.hpp"
#endif

#include "controlInput.hpp"
#include "sketchMenu.hpp"

class sketchamesh : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    
    //    #if TARGET == 0
    GuiControl gui;
    //    #elif TARGET == 1
    GpioControl hardware;
    //    #endif
    
    SketchMenu menu;
    ControlInput input;
    ofMesh mesh;
    ofPoint position;
    ofPoint cubeOrigin;
    int action;
    int mode;
    bool modeReady;
    ofImage display;
    ofImage logo;
    int joinIndex;
    
    ofEasyCam camera;
    ofPoint camPos;
    
    void setupMesh();
    void resetMesh();
    void addVertex(ofPoint pos);
    void drawCursor(ofPoint pos);
    
    ofPoint getWithoutRotation(ofPoint p);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};
