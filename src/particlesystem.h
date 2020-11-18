#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#pragma once
#include "ofMain.h"
#include "particle.h"
#include "dropparticle.h"

class particleSystem
{
public:
    particleSystem();

    std::vector < dropParticle > dropParticles;


    void addDropParticle();
    void run(ofImage& i);
    int ofw;
    int ofh;

    ofTrueTypeFont	roboto32;

};

#endif // PARTICLESYSTEM_H
