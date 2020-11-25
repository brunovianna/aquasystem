#ifndef DROPPARTICLE_H
#define DROPPARTICLE_H
#pragma once
#include "ofMain.h"
#include "particle.h"
#include "ofxOpenCv.h"

class dropParticle : public particle
{
public:
    dropParticle();
    dropParticle(glm::vec2 position);
    void display();
    int run(vector <ofPolyline> blobs);
    int update(vector <ofPolyline> blobs);
    bool isDead();
    bool dead, touch;
    ofColor reddish;
    glm::vec2 touch_point;
};

#endif // DROPPARTICLE_H
