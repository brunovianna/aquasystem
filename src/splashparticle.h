#ifndef SPLASHPARTICLE_H
#define SPLASHPARTICLE_H

#include "particle.h"


class splashParticle : public particle
{
public:
    splashParticle();
    splashParticle(glm::vec2 position);
    void display();
    void run();
    void update();
    bool isDead();
    int lifetime;
    int side;
    float speed;

};

#endif // SPLASHPARTICLE_H
