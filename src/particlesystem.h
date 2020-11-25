#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#pragma once
#include "ofMain.h"
#include "particle.h"
#include "dropparticle.h"
#include "splashparticle.h"
#include "ofxOpenCv.h"

class particleSystem
{
public:
    particleSystem();

    std::vector < dropParticle > dropParticles;
    std::vector < splashParticle > splashParticles;


    void addDropParticle();
    void addSplashParticle(glm::vec2 tp);
    void run(vector <ofPolyline> blobs);
    int ofw;
    int ofh;

    ofTrueTypeFont	roboto32;

};

#endif // PARTICLESYSTEM_H
