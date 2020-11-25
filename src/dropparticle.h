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
    int run(vector <ofPolyline> blobs);
    int update(vector <ofPolyline> blobs);
    bool isDead();
    bool touch;
    glm::vec2 touch_point;
};

#endif // DROPPARTICLE_H
