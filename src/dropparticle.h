#ifndef DROPPARTICLE_H
#define DROPPARTICLE_H
#pragma once
#include "ofMain.h"
#include "particle.h"



class dropParticle : public particle
{
public:
    dropParticle();
    dropParticle(glm::vec2 position);
    void display();
    int run(ofImage& canvasRef);
    int update(ofImage& canvasRef);
    bool isDead();
    bool dead;
    ofColor reddish;

};

#endif // DROPPARTICLE_H
