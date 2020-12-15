#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(24);

    ofw = ofGetWindowWidth();
    ofh = ofGetWindowHeight();


    ofTrueTypeFont::setGlobalDpi(72);
    roboto_gui.load("Roboto-Medium.ttf",16,true,true);
    show_gui = false;

    ofSetBackgroundAuto(false);

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
    box2d.setFPS(24.0);

    //box2d.registerGrabbing();
    //box2d.createBounds();

    //(b2World * _b2world, int _maxCount, float _lifetime, float _radius, float _particleSize, ofColor _color){
    water_particles.setup(box2d.getWorld(),1000,1000,2.f,3.f,ofColor(161,200,226));

    // water_particles.loadImage("drop_circle_a.png");
    //particles.setRadius(5.f);

    ps.water_particles = &water_particles;
    ps.max_water_drops = max_water_drops;


   t0.Set(b2Vec2(0,0),0.f);
   ofx_invert_b2scale = 1/OFX_BOX2D_SCALE;

   ps.velocity_x = velocity_x;
   ps.velocity_y = velocity_y;

}

//--------------------------------------------------------------
void ofApp::update(){

    ps.velocity_x = velocity_x;
    ps.velocity_y = velocity_y;


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

    //some pesky particles end up inside the shapes, so let's get rid of them
    //should i really erase them? or just paint over the blobs? what is faster?
   // for (auto p: polyShapes)
   // {
   //    b2Vec2 points[3];
   //    for (auto t: p->triangles)
   //    {
   //
   //        points[0].Set( t.a.x,t.a.y);
   //        points[1].Set( t.b.x,t.b.y);
   //        points[2].Set( t.c.x,t.c.y);
   //
   //        b2PolygonShape bs;
   //        bs.Set(points,3);
   //        for (int i=0;i<water_particles.getParticleCount();i++)
   //        {
   //            if (bs.TestPoint(t0,water_particles.particleSystem->GetPositionBuffer()[i]*OFX_BOX2D_SCALE))
   //                water_particles.particleSystem->DestroyParticle(i);
   //        }
   //
   //    }
   // }


    box2d.update();
    ofLog(OF_LOG_NOTICE,  "particle count"+to_string(water_particles.getParticleCount()));

    int inv_drops = (ofGetTargetFrameRate()/(float)num_raindrops);
    if (ofGetFrameNum()%inv_drops==0)
      ps.addDropParticle();



}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDisableAlphaBlending();
    ofBackground(ofColor::black);

    //uncomment to draw the depth image under the drops
    //depthTex.draw(0,0);



    //water_particles.draw();

    ps.run(blobs);


    //draw the contour shapes as used by the particle system
    ofSetColor(ofColor::gray);
    for (auto p: polyShapes)
    {
       for (auto t: p->triangles)
       {
           ofDrawTriangle (t.a.x,t.a.y,0,t.b.x,t.b.y,0,t.c.x,t.c.y,0);
       }
    }

// not working in the raspi
// //    option to use the brightness of the image as alpha
//     ofImage mask;
//     ofSetColor(ofColor::white);
//     ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//     mask.setImageType(OF_IMAGE_COLOR_ALPHA);
//     mask.setFromPixels(cv_grayscale.getPixels());
//
//     //mask.getPixels().setChannel(3, mask.getPixels().getChannel(0));
//     //mask.getTexture().setAlphaMask(mask.getTexture());
//     mask.getTexture().setSwizzle(GL_TEXTURE_SWIZZLE_A,GL_RED);
//
//     mask.draw(0,0);
//     ofDisableBlendMode();
//


// this just uses add mode, doesn't look so good
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
//    ofSetColor(ofColor::white);
//    depthTex.draw(0,0);
//    ofDisableBlendMode();

  if (show_gui)
  {
    ofSetColor(ofColor::yellow);
    roboto_gui.drawString ("Gotas por segundo: "+to_string(num_raindrops)+" (i/o para cambiar)", 20,20);
    roboto_gui.drawString ("Número máximo de gotas azules simultaneas: "+to_string(max_water_drops)+"  (k/l para cambiar)", 20,50);
    roboto_gui.drawString ("Velocidad horizontal: "+to_string(velocity_x)+" (q/w para cambiar)", 20,80);
    roboto_gui.drawString ("Velocidad vertical: "+to_string(velocity_y)+"  (a/s para cambiar)", 20,110);
    roboto_gui.drawString ("Rastro: "+to_string(trails_amount)+"  (z/x para cambiar)", 20,140);
    roboto_gui.drawString (to_string(ofGetFrameRate())+" fps", ofw-200,20);
    roboto_gui.drawString (to_string(water_particles.getParticleCount())+" gotas azules", ofw-200,40);
    ofSetColor(ofColor::white);
  }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  switch (key)
  {    case OF_KEY_RETURN:
      case ' ':
        show_gui = !show_gui;
      break;
      case 'i':
        if (num_raindrops > 0) num_raindrops--;
      break;
      case 'o':
        if (num_raindrops < 20) num_raindrops++;
      break;
      case 'k':
        if (max_water_drops > 9) max_water_drops-=10;
      break;
      case 'l':
        if (max_water_drops < 2000) max_water_drops+=10;
      break;
      case 'q':
        if (velocity_x > -20.0) velocity_x-=.5f;
      break;
      case 'w':
        if (velocity_x < 20.0) velocity_x+=.5f;
      break;
      case 'a':
        if (velocity_y > 5.0f) velocity_y--;
      break;
      case 's':
        if (velocity_y < 100.f) velocity_y++;
      break;
    }
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
        water_particles.createParticle(position, velocity);
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
