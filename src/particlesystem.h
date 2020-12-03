#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#pragma once
#include "ofMain.h"
#include "particle.h"
#include "dropparticle.h"
#include "splashparticle.h"
#include "wordparticle.h"
#include "explodeparticle.h"
#include "ofxOpenCv.h"

class particleSystem
{
public:
    particleSystem();

    std::vector < dropParticle > dropParticles;
    std::vector < splashParticle > splashParticles;
    std::vector < wordParticle > wordParticles;
    std::vector < explodeParticle > explodeParticles;


    void addDropParticle();
    void addSplashParticle(glm::vec2 tp);
    void addWordParticle(float x);
    void addExplodeParticle(glm::vec2 _pos,  ofTrueTypeFont _font, string _text);
    void run(vector <ofPolyline> blobs);
    int ofw;
    int ofh;

    ofTrueTypeFont	roboto;
    string agua_text, explosion_text;

};

#endif // PARTICLESYSTEM_H
