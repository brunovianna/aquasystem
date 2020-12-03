#ifndef DROPPARTICLE_H
#define DROPPARTICLE_H
#pragma once
#include "ofMain.h"
#include "particle.h"
#include "ofxOpenCv.h"

class dropParticle : public particle
{
public:

    dropParticle(glm::vec2 position);
    void display();
    void run(vector <ofPolyline> blobs);
    void update(vector <ofPolyline> blobs);
    bool isDead();
    bool touch, ground, explode;
    glm::vec2 touch_point;
};

#endif // DROPPARTICLE_H
