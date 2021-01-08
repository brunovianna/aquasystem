#ifndef DROPPARTICLE_H
#define DROPPARTICLE_H
#pragma once
#include "ofMain.h"
#include "particle.h"
#include "ofxOpenCv.h"
#include "ofxLiquidFun.h"

class dropParticle : public particle
{
public:

    dropParticle(glm::vec2 position, glm::vec2 velocity,  ofImage &drop_image, int *_trails_amount);
    void display(ofFbo &bg);
    void run(vector <ofPolyline> blobs, ofFbo &bg);
    void update(vector <ofPolyline> blobs);
    bool isDead();
    bool touch, ground, explode;
    glm::vec2 touch_point;
    ofImage drop_image;
    double angle;
    int *trails_amount;
};

#endif // DROPPARTICLE_H
