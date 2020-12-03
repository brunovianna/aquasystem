#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);

    ofw = ofGetWindowWidth();
    ofh = ofGetWindowHeight();


    ofTrueTypeFont::setGlobalDpi(72);

    //playback from file - uncomment below
    //rs2::config cfg;
    //cfg.enable_device_from_file("data/b.bag");
    //pipe.start(cfg); //File will be opened in read mode at this point


    //live cam -- uncomment below
    pipe.start();

    device = pipe.get_active_profile().get_device();

    // filter settings
    thr_filter.set_option(RS2_OPTION_MIN_DISTANCE, depth_clipping_distance_near);
    thr_filter.set_option(RS2_OPTION_MAX_DISTANCE, depth_clipping_distance_far);

    _colorizer.set_option(RS2_OPTION_MAX_DISTANCE, depth_clipping_distance_far);
    _colorizer.set_option(RS2_OPTION_MIN_DISTANCE, depth_clipping_distance_near);
    _colorizer.set_option(RS2_OPTION_COLOR_SCHEME, 2);

    box2d.init();
    box2d.setGravity(0, 10);
    box2d.setFPS(30.0);

    box2d.registerGrabbing();
    box2d.createBounds();

    particles.setup(box2d.getWorld());

}

//--------------------------------------------------------------
void ofApp::update(){





    //comment below for live cam
    if (!pipe.poll_for_frames(&frame_set)) // Check if new frames are ready
    {
        return;
    }


    //uncomment below for live cam
    //frame_set = pipe.wait_for_frames();



    rs2::depth_frame  depth = frame_set.get_depth_frame();
    rs2::video_frame  cam = frame_set.get_color_frame();
    depth = thr_filter.process(depth);
    rs2::video_frame depth_image = _colorizer.colorize(depth);




    //Only process if one of them is unavailable
    if (depth && cam)
    {

        int depthWidth = depth_image.get_width();
        int depthHeight = depth_image.get_height();
        uint8_t *buff = (uint8_t*)depth_image.get_data();
        depthTex.loadData(buff, depthWidth, depthHeight, GL_RGB);

        cv_color.setFromPixels(buff,depthWidth,depthHeight);
        cv_grayscale = cv_color;
        // Find contours whose areas are betweeen 20 and 25000 pixels
        // "Find holes" is true, so we'll also get interior contours.
        contourFinder.findContours(cv_grayscale, 2000, 1000000, 10, false);

    }

    blobs.clear();
    polyShapes.clear();

    for (int i=0; i<contourFinder.nBlobs; i++){
        ofPolyline blob(contourFinder.blobs[i].pts);
        ofPolyline simple;
        //blob.simplify(0.9f);
        //simple = blob.getResampledBySpacing(30.f);
        simple = blob.getSmoothed(8,0.1);
        //simple = simple.getResampledByCount(30.f);
        blobs.push_back(simple);
        auto box2dpoly = std::make_shared<ofxBox2dPolygon>();
        box2dpoly->addVertices(simple.getVertices());
        box2dpoly->triangulatePoly();

        box2dpoly->create(box2d.getWorld());
        polyShapes.push_back(box2dpoly);

    }




box2d.update();


}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(ofColor::black);
    ofSetColor(ofColor::white);
    depthTex.draw(0,0);


   // if (ofGetFrameNum()%2==0)
    ps.addDropParticle();

    ps.run(blobs);
    particles.draw();

    ofSetColor(ofColor::lightGray);
    for (auto b: blobs) b.draw();
    ofSetColor(ofColor::yellowGreen);
    for (auto p: polyShapes) p->draw();


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
    for (int i = 0; i < 20; i++) {
        float radius = 40;
        float x = cos(ofRandom(PI*2.0)) * radius + mouseX;
        float y = sin(ofRandom(PI*2.0)) * radius + mouseY;
        ofVec2f position = ofVec2f(x, y);
        ofVec2f velocity = ofVec2f(ofRandom(-200, 200), ofRandom(-200, 200));
        particles.createParticle(position, velocity);
    }
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

