#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    body.load("body.png");

    aguaStr = "agua";
    h = 600;
    w = 800;
    ofSetWindowShape(w,h);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofImage canvas;
    ofImage& canvasRef = canvas;

    ofBackground(ofColor::black);

    body.draw(w/2, h-body.getWidth());
    //body.draw(mouseX-(body.getWidth()/2), h-body.getWidth());
    if (ofGetFrameNum()%10==0) ps.addDropParticle();

    canvas.grabScreen(0,0,w,h);
    ps.run(canvasRef);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
