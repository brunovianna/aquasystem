#include "ofMain.h"
#include "ofApp.h"


//========================================================================
int main( ){

    ofGLFWWindowSettings mainSetting;
    mainSetting.setGLVersion(4,1);
    mainSetting.setSize(1280, 720);
    mainSetting.setPosition(ofVec2f(0, 0));
    mainSetting.decorated = false;
    mainSetting.windowMode = OF_WINDOW;
    //mainSetting.numSamples = 8;
    ofCreateWindow(mainSetting);


    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());

}
