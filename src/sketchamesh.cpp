// 0 = ofxGui, 1= ofxGPIO
#define TARGET 1

#include "sketchamesh.h"

//--------------------------------------------------------------
// basic initialisation
void sketchamesh::setup() {
    if (TARGET == 1) {
        // depth test breaks ofxGui interface,
        // only activate on hardware version.
        ofSetDepthTest(true);
        ofHideCursor();
    }
    setupMesh();
    camPos = ofPoint(0, 0, 1000);
    mode = 0;
    modeReady = false;
    joinIndex = 0;
    
    camera.setPosition(camPos);
    camera.setTarget(glm::vec3(0, 0, 0));
    camera.lookAt(glm::vec3(0, 0, 0));
    
    logo.load("images/logo.png");
}

// set mesh properties and initialise a vertex
void sketchamesh::setupMesh() {
    mesh.enableIndices();
    mesh.enableColors();
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    
    if (TARGET == 0) {
        input = gui.getInput();
    } else if (TARGET == 1) {
        input = hardware.getInput();
    }
    
    position = input.getRelativePosition();
    addVertex(position);
}

// add vertex at a given point
void sketchamesh::addVertex(ofPoint pos) {
    mesh.addVertex(pos);
    mesh.addColor(ofColor(ofRandom(172)));
    mesh.addIndex((int) mesh.getNumVertices() - 1);
}

// empty the mesh and reset the 'join' index counter
void sketchamesh::resetMesh() {
    mesh.clear();
    mesh.addVertex(position);
    mesh.addIndex((int) mesh.getNumVertices() - 1);
    mesh.addColor(ofColor(0));
    joinIndex = 0;
}

//--------------------------------------------------------------
void sketchamesh::update(){
    if (action == 1) { // reset requested
        resetMesh();
        action = 0;
    } else if (action == 3 || action == 4 || action == 5 || action == 6) { // set toggle mode
        mode = action - 3;
        action = 0;
    }
    
    if (TARGET == 0) {
        input = gui.getInput();
    } else if (TARGET == 1) {
        input = hardware.getInput();
    }
    
    // update position and get the index of the latest vertex
    position = input.getRelativePosition();
    int lastIndex = (int) mesh.getNumVertices() - 1;
    
    
    if (!input.toggle) { // basic sketching
        modeReady = false;
        ofPoint previous = mesh.getVertex(lastIndex);
        if (position.distance(previous) > 3) {
            addVertex(position);
        }
    } else {
        if (mode == 0) { // placing vertices
            if (!modeReady) {
                addVertex(position);
                modeReady = true;
            }
            mesh.setVertex(lastIndex, position);
        } else if (mode == 1) { // drawing cubes
            int lastIndex = (int) mesh.getNumVertices() - 1;
            if (!modeReady) {
                // adding and connection vertices
                for (int i = 0; i < 7; i++) {
                    addVertex(position);
                }
                lastIndex = (int) mesh.getNumVertices() - 1;
                int indices[10] = {3, 2, 7, 4, 5, 0, 1, 6, 1, 0};
                for (int i = 0; i < 10; i ++) {
                    mesh.addIndex(lastIndex - indices[i]);
                }
                cubeOrigin = input.getRelativePosition();
                modeReady = true;
            }
            // updating corner positions
            ofPoint o = input.relToAbs(cubeOrigin);
            ofPoint p = input.getAbsolutePosition();
            mesh.setVertex(lastIndex - 7, input.absToRel(o));
            mesh.setVertex(lastIndex - 6, input.absToRel(ofPoint(o.x, o.y, p.z)));
            mesh.setVertex(lastIndex - 5, input.absToRel(ofPoint(o.x, p.y, p.z)));
            mesh.setVertex(lastIndex - 4, input.absToRel(ofPoint(o.x, p.y, o.z)));
            mesh.setVertex(lastIndex - 3, input.absToRel(ofPoint(p.x, p.y, o.z)));
            mesh.setVertex(lastIndex - 2, input.absToRel(ofPoint(p.x, o.y, o.z)));
            mesh.setVertex(lastIndex - 1, input.absToRel(ofPoint(p.x, o.y, p.z)));
            mesh.setVertex(lastIndex, input.absToRel(p));
        } else if (mode == 2) { // drawing polys
            if (!modeReady) {
                addVertex(position);
                lastIndex = (int) mesh.getNumVertices() - 1;
                mesh.addIndex(lastIndex - 2);
                mesh.addIndex(lastIndex);
                modeReady = true;
            }
            lastIndex = (int) mesh.getNumVertices() - 1;
            mesh.setVertex(lastIndex, position);
        } else if (mode == 3) { // joining vertices
            if (!modeReady) {
                for (int i = joinIndex; i < mesh.getNumVertices() - 1; i += 10) {
                    for (int j = joinIndex; j < mesh.getNumVertices() - 1; j += 10) {
                        mesh.addIndex(i);
                        mesh.addIndex(j);
                    }
                }
                joinIndex = (int) mesh.getNumVertices() - 1;
                modeReady = true;
            }
        }
    }
    menu.setNumVertices((int) mesh.getNumVertices());
}

//--------------------------------------------------------------
void sketchamesh::draw(){
    ofBackground(190);
    
    camera.begin();
    
    ofPushMatrix();
    ofRotateXDeg(input.rx);
    ofRotateYDeg(input.ry);
    ofRotateZDeg(input.rz);
    mesh.draw();
    ofPopMatrix();
    
    drawCursor(input.getAbsolutePosition());
    
    camera.end();
    
    // export screenshot before drawing in the menu/gui
    if (action == 2) {
        logo.draw(ofPoint(ofGetWidth() - 201, ofGetHeight() - 53), 181, 33);
        display.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        display.save(ofGetTimestampString() + ".png");
        action = 0;
    }
    
    if (TARGET == 0) {
        gui.draw();
    }
    
    menu.draw();
}

void sketchamesh::drawCursor(ofPoint pos) {
    ofSetColor(255, 128, 128);
    ofSetLineWidth(2);
    ofDrawLine(pos + ofVec3f(0, 0, 20), pos + ofVec3f(0, 0, -20));
    ofDrawLine(pos + ofVec3f(0, 20, 0), pos + ofVec3f(0, -20, 0));
    ofDrawLine(pos + ofVec3f(20, 0, 0), pos + ofVec3f(-20, 0, 0));
    ofSetLineWidth(1);
}

//--------------------------------------------------------------
void sketchamesh::keyPressed(int key){
    if (key == 's') {
        mesh.save("mesh.ply");
    } else if (key == 'l') {
        mesh.load("mesh.ply");
    } else if (key == 'r') {
        resetMesh();
    }
}

//--------------------------------------------------------------
void sketchamesh::keyReleased(int key){
    
}

//--------------------------------------------------------------
void sketchamesh::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void sketchamesh::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void sketchamesh::mousePressed(int x, int y, int button){
    // pass clicks to the menu
    action = menu.checkClick(x, y);
}

//--------------------------------------------------------------
void sketchamesh::mouseReleased(int x, int y, int button){
    // snap camera back to default
    camera.reset();
    camera.setPosition(camPos);
    camera.setTarget(ofPoint(0, 0, 0));
    camera.lookAt(ofPoint(0, 0, 0));
    // show the menu button on touch release
    menu.toggleVisible = true;
    menu.lastShown = ofGetFrameNum();
}

//--------------------------------------------------------------
void sketchamesh::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void sketchamesh::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void sketchamesh::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void sketchamesh::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void sketchamesh::dragEvent(ofDragInfo dragInfo){ 
    
}
