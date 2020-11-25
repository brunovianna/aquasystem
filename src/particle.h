#ifndef PARTICLE_H
#define PARTICLE_H
#pragma once
#include "ofMain.h"

class particle
{
public:
    particle();
    particle(glm::vec2 p, glm::vec2 v, glm::vec2 a);
    virtual void run();
    virtual void update();
    virtual void display();
    virtual bool isDead();

    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;

    int ofh;
    int ofw;

    bool dead;


};

#endif // PARTICLE_H
