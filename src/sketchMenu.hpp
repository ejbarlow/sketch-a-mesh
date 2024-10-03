//
//  sketchMenu.hpp
//  sketchamesh-beta
//
//  Created by ed on 14/03/2023.
//

#ifndef sketchMenu_hpp
#define sketchMenu_hpp

#include <stdio.h>
#include "ofMain.h"
class MenuButton {
public:
    MenuButton();
    MenuButton(int _x, int _y, int _w, int _h, string _caption);
    
    int x;
    int y;
    int w;
    int h;
    string caption;
    
    bool active;
    
    void setup();
    void draw();
};

class SketchMenu {
public:
    SketchMenu();
    
    int btnSize;
    int margin;
    int activeMode;
    int numVertices;
    
    bool active;
    bool toggleVisible;
    int lastShown;
    MenuButton menuToggle;
    MenuButton reset;
    MenuButton screenshot;
    MenuButton exit;
    MenuButton vertex;
    MenuButton cube;
    MenuButton poly;
    MenuButton join;
    
    void setMode(int mode);
    
    ofImage logo;
    
    void draw();
    int checkClick(int x, int y);
    bool checkButton(int x, int y, MenuButton btn);
    void setNumVertices(int n);
};

#endif /* sketchMenu_hpp */
