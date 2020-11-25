#pragma once

#include "ofMain.h"
#include <librealsense2/rs.hpp>
#include "particlesystem.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofImage body;
    particleSystem ps;

    int ofw;
    int ofh;

    string aguaStr;



    //const rs2::align align	( 	rs2_stream  	align_to	);
    rs2::pipeline pipe;
    rs2::device device;
    rs2::colorizer color_map;
    rs2::colorizer  _colorizer;
    rs2::frame colored_depth;
    rs2::frame colored_filtered;
    rs2::threshold_filter thr_filter;
    rs2::frameset frame_set;




    ofImage mask;
    ofTexture depthTex;
    ofTexture camTex;

    void setMaskFromDepth(ofImage& mask, rs2::depth_frame depth);

    void remove_background(rs2::video_frame& other, const rs2::depth_frame& depth_frame, float depth_scale,  float near, float far);

    float depth_scale;
    float get_depth_scale(rs2::device dev);

    // Define a variable for controlling the distance to clip
    float depth_clipping_distance_far = 0.5f;
    float depth_clipping_distance_near = 0.3f;

    ofxCvGrayscaleImage cv_grayscale;
    ofxCvColorImage cv_color;

    ofxCvContourFinder		contourFinder;

};

extern rs2::align align_me;
