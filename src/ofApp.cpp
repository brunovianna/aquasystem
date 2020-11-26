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


    // Box2d
    box2d.init();
    box2d.setGravity(0, 30);
    box2d.createGround();
    box2d.setFPS(15.0);

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
    people.clear();

    for (int i=0; i<contourFinder.nBlobs; i++){
        ofPolyline blob(contourFinder.blobs[i].pts);
        //blob.simplify();
        blobs.push_back(blob);
        //blob.draw();

        auto poly = std::make_shared<ofxBox2dPolygon>();
        poly->addVertices(contourFinder.blobs[i].pts);
        //no density, bounce, friction
        poly->setPhysics(0.0, 0.0, 0.0);
        poly->triangulate();
        poly->create(box2d.getWorld());
        people.push_back(poly);
    }


    if ((int)ofRandom(0, 10) == 0) {
            auto c = make_shared<ofxBox2dCircle>();

            c->setPhysics(0.2, 0.2, 0.002);
            c->setup(box2d.getWorld(), ofRandom(1, 320), -20, ofRandom(3, 10));
            c->setVelocity(0, 15); // shoot them down!
            circles.push_back(c);
        }

        box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(ofColor::black);
    depthTex.draw(0,0);



   // if (ofGetFrameNum()%2==0)
    ps.addDropParticle();

    for(auto &person : people) {
      ofFill();
      ofSetHexColor(0x7777a7);
      person->draw();
    }
    ofSetHexColor(0xbbbbbb);
    for (auto blob: blobs) blob.draw();

    ps.run(blobs);


    for(auto &circle : circles) {
      ofFill();
      ofSetHexColor(0xc0dd3b);
      circle->draw();
    }



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
