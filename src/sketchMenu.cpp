//
//  sketchMenu.cpp
//  sketchamesh-beta
//
//  Created by ed on 14/03/2023.
//

#include "sketchMenu.hpp"
MenuButton::MenuButton() {
    
}

MenuButton::MenuButton(int _x, int _y, int _w, int _h, string _caption) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    caption = _caption;
    active = false;
}

void MenuButton::draw() {
    if (active) {
        ofSetColor(0);
    } else {
        ofSetColor(32);
    }
    ofDrawRectangle(x, y, w, h);
    
    if (active) {
        ofSetColor(190);
        ofDrawRectangle(x + 5, y + 5, w - 10, h - 10);
        ofSetColor(0);
        ofDrawRectangle(x + 10, y + 10, w - 20, h - 20);
    }
    
    ofBitmapFont sizeCheck;
    ofRectangle bounds = sizeCheck.getBoundingBox(caption, 0, 0);
    
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    ofDrawBitmapStringHighlight(caption, x + (w / 2) - (bounds.width / 2), y + (h / 2));
}

SketchMenu::SketchMenu() {
    btnSize = 100;
    margin = 10;
    active = false;
    activeMode = 0;
    toggleVisible = false;
    menuToggle = MenuButton(0, ofGetHeight() - btnSize, btnSize, btnSize, "menu");
    reset = MenuButton(0, ofGetHeight() - (btnSize * 2 + margin), btnSize, btnSize, "reset");
    screenshot = MenuButton(btnSize + margin, ofGetHeight() - (btnSize * 2 + margin), btnSize, btnSize, "screenshot");
    exit = MenuButton((btnSize + margin) * 2, ofGetHeight() - (btnSize * 2 + margin), btnSize, btnSize, "exit");
    vertex = MenuButton(0, ofGetHeight() - (btnSize * 3 + margin * 2), btnSize, btnSize, "vertex");
    cube = MenuButton(btnSize + margin, ofGetHeight() - (btnSize * 3 + margin * 2), btnSize, btnSize, "cube");
    poly = MenuButton((btnSize + margin) * 2, ofGetHeight() - (btnSize * 3 + margin * 2), btnSize, btnSize, "poly");
    join = MenuButton((btnSize + margin) * 3, ofGetHeight() - (btnSize * 3 + margin * 2), btnSize, btnSize, "join");
    
    logo.load("images/logo.png");
    
    setMode(0);
}

void SketchMenu::setNumVertices(int n) {
    numVertices = n;
}

void SketchMenu::draw() {
    if (active) {
        menuToggle.caption = "back";
        menuToggle.draw();
        reset.draw();
        screenshot.draw();
        exit.draw();
        vertex.draw();
        cube.draw();
        poly.draw();
        join.draw();
        logo.draw(ofPoint(125, ofGetHeight() - 66), 181, 33);
        string count = std::to_string(numVertices) + " vertices / ";
        string fps = std::to_string((int) ofGetFrameRate()) + "FPS";
        ofDrawBitmapStringHighlight(count + fps, 0, 20);
    } else if (toggleVisible) {
        menuToggle.caption = "menu";
        menuToggle.draw();
        if (ofGetFrameNum() - lastShown > 120) {
            toggleVisible = false;
        }
    }
}

int SketchMenu::checkClick(int x, int y) {
    if (checkButton(x, y, menuToggle)) {
        active = !active;
        return 0;
    }
    
    if (active) {
        if (checkButton(x, y, reset)) {
            active = false;
            return 1;
        }
        if (checkButton(x, y, screenshot)) {
            active = false;
            return 2;
        }
        if (checkButton(x, y, exit)) {
            ofExit();
        }
        if (checkButton(x, y, vertex)) {
            active = false;
            setMode(0);
            return 3;
        }
        if (checkButton(x, y, cube)) {
            active = false;
            setMode(1);
            return 4;
        }
        if (checkButton(x, y, poly)) {
            active = false;
            setMode(2);
            return 5;
        }
        if (checkButton(x, y, join)) {
            active = false;
            setMode(3);
            return 6;
        }
    }
    
    return 0;
}

void SketchMenu::setMode(int mode) {
    activeMode = mode;
    vertex.active = mode == 0;
    cube.active = mode == 1;
    poly.active = mode == 2;
    join.active = mode == 3;
}

bool SketchMenu::checkButton(int x, int y, MenuButton btn) {
    bool a = x > btn.x;
    bool b = x < btn.x + btn.w;
    bool c = y > btn.y;
    bool d = y < btn.y + btn.h;
    
    if (a && b && c && d) {
        return true;
    }
    
    return false;
}
