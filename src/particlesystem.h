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
#include "ofxLiquidFun.h"

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
    void addWaterParticle(glm::vec2 wp);
    void addWordParticle(float x);
    void addExplodeParticle(glm::vec2 _pos,  ofTrueTypeFont _font, string _text);
    void run(vector <ofPolyline> blobs);
    int ofw;
    int ofh;
    float velocity_x;
    float velocity_y;

    ofImage drop_image;
    ofFbo bg_fbo;


    ofTrueTypeFont agua_font;
    string agua_text, explosion_text;
    ofxBox2dParticleSystem * water_particles;
    int max_water_drops;

    b2ParticleDef water_pd;

    void draw_circles();
    int remove_outside_circles ();
};

#endif // PARTICLESYSTEM_H
