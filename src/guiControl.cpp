//
//  guiControl.cpp
//  sketchamesh-beta
//
//  Created by ed on 14/03/2023.
//

#include "guiControl.hpp"

GuiControl::GuiControl() {
    int halfW = ofGetWidth() / 2;
    int halfH = ofGetHeight() / 2;
    
    panel.setup("panel");
    panel.setPosition(20, 0);
    panel.add(toggle.set("switch", false));
    panel.add(x.set("x_pot", 0, -halfW, halfW));
    panel.add(y.set("y_pot", 0, halfH, -halfH));
    panel.add(z.set("z_pot", 0, -200, 200));
    panel.add(rx.set("x_slider", 0, -180, 180));
    panel.add(ry.set("y_slider", 0, -180, 180));
    panel.add(rz.set("z_slider", 0, -180, 180));
}

void GuiControl::draw() {
    panel.draw();
}

ControlInput GuiControl::getInput() {
    input.toggle = toggle;
    input.x = x;
    input.y = y;
    input.z = z;
    input.rx = rx;
    input.ry = ry;
    input.rz = rz;
    return input;
}
