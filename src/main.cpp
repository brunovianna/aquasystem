#include "ofMain.h"
#include "ofApp.h"


//========================================================================
int main( ){


    #ifdef TARGET_RASPBERRY_PI
    ofGLESWindowSettings mainSetting;
    mainSetting.setGLESVersion(3); //if i set this version, it won't draw the water particle shape anymore. so i wrote my own in particlesystem.cpp
    mainSetting.windowMode = OF_FULLSCREEN;
    #else
    ofGLFWWindowSettings mainSetting;
    mainSetting.setGLVersion(3,2); //if i set this version, it won't draw the water particle shape anymore. so i wrote my own in particlesystem.cpp
    mainSetting.decorated = false;
    mainSetting.windowMode = OF_WINDOW;
    #endif
    mainSetting.setSize(1280, 720);
    mainSetting.setPosition(ofVec2f(0, 0));

    //mainSetting.numSamples = 8;´
    ofCreateWindow(mainSetting);


    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());

}
