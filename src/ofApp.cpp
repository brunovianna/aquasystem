#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);


    aguaStr = "agua";
    ofw = ofGetWindowWidth();
    ofh = ofGetWindowHeight();


    //playback from file - uncomment below
    //rs2::config cfg;
    //cfg.enable_device_from_file("data/b.bag");
    //pipe.start(cfg); //File will be opened in read mode at this point


    //live cam -- uncomment below
    pipe.start();

    device = pipe.get_active_profile().get_device();

    // Each depth camera might have different units for depth pixels, so we get it here
    // Using the pipeline's profile, we can retrieve the device that the pipeline uses
    depth_scale = get_depth_scale(device);

    //playback from file - uncomment below
    //rs2::playback playback = device.as<rs2::playback>();




    // filter settings
    thr_filter.set_option(RS2_OPTION_MIN_DISTANCE, depth_clipping_distance_near);
    thr_filter.set_option(RS2_OPTION_MAX_DISTANCE, depth_clipping_distance_far);

    _colorizer.set_option(RS2_OPTION_MAX_DISTANCE, depth_clipping_distance_far);
    _colorizer.set_option(RS2_OPTION_MIN_DISTANCE, depth_clipping_distance_near);
    _colorizer.set_option(RS2_OPTION_COLOR_SCHEME, 2);


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


    //auto depth = frames.get_depth_frame();

    //Only process if one of them is unavailable
    if (depth && cam)
    {

        int depthWidth = depth_image.get_width();
        int depthHeight = depth_image.get_height();
        uint8_t *buff = (uint8_t*)depth_image.get_data();
        depthTex.loadData(buff, depthWidth, depthHeight, GL_RGB);

        //remove_background(cam, depth, depth_scale,depth_clipping_distance_near, depth_clipping_distance_far);

        //buff = (uint8_t*)cam.get_data(); //now cam has bg removed
        cv_color.setFromPixels(buff,depthWidth,depthHeight);
        cv_grayscale = cv_color;
        // Find contours whose areas are betweeen 20 and 25000 pixels
        // "Find holes" is true, so we'll also get interior contours.
        contourFinder.findContours(cv_grayscale, 2000, 1000000, 10, false);



    }



}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(ofColor::black);
    depthTex.draw(0,0);

    vector <ofPolyline> blobs;

    for (int i=0; i<contourFinder.nBlobs; i++){
        ofPolyline blob(contourFinder.blobs[i].pts);
        //blob.simplify();
        blobs.push_back(blob);
        blob.draw();
    }


    if (ofGetFrameNum()%2==0) ps.addDropParticle();

    ps.run(blobs);

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

void ofApp::setMaskFromDepth(ofImage& mask, rs2::depth_frame depth) {
    ofPixels pixels = mask.getPixels();


    for (int i=0;i<mask.getWidth();i++) {
        for (int j =0;j<mask.getHeight();j++) {
            int pixelIndex = j*mask.getWidth()+i;
                float distance = depth.get_distance(i,j);
                if ((distance> depth_clipping_distance_near)&&(distance<depth_clipping_distance_far)) {
                    pixels[pixelIndex] = 120;

                }
        }
    }


    mask.setFromPixels(pixels);
}

void ofApp::remove_background(rs2::video_frame& other_frame, const rs2::depth_frame& depth_frame, float depth_scale, float clipping_distance_near, float clipping_dist_far) {

    const uint16_t* p_depth_frame = reinterpret_cast<const uint16_t*>(depth_frame.get_data());
    uint8_t* p_other_frame = reinterpret_cast<uint8_t*>(const_cast<void*>(other_frame.get_data()));

    int width = other_frame.get_width();
    int height = other_frame.get_height();
    int other_bpp = other_frame.get_bytes_per_pixel();

    #pragma omp parallel for schedule(dynamic) //Using OpenMP to try to parallelise the loop
    for (int y = 0; y < height; y++)
    {
       auto depth_pixel_index = y * width;
       for (int x = 0; x < width; x++, ++depth_pixel_index)
       {
           // Get the depth value of the current pixel
           auto pixels_distance = depth_scale * p_depth_frame[depth_pixel_index];

           // Calculate the offset in other frame's buffer to current pixel
           auto offset = depth_pixel_index * other_bpp;

           // Check if the depth value is invalid (<=0) or greater than the threashold
           if (pixels_distance < clipping_distance_near || pixels_distance > clipping_dist_far)
           {

               // Set pixel to black color (0x999999) if its off limits
               std::memset(&p_other_frame[offset], 0x00, other_bpp);
           } else {
               // set pixel to white where the rain will touch
               std::memset(&p_other_frame[offset], 0xffffff, other_bpp);

           }
       }
    }

}

float ofApp::get_depth_scale(rs2::device dev)
{
    // Go over the device's sensors
    for (rs2::sensor& sensor : dev.query_sensors())
    {
        // Check if the sensor if a depth sensor
        if (rs2::depth_sensor dpt = sensor.as<rs2::depth_sensor>())
        {
            return dpt.get_depth_scale();
        }
    }
    throw std::runtime_error("Device does not have a depth sensor");
}
