#include "particle.h"

particle::particle()
{
    position = ofDefaultVec2(0,0);
    velocity = ofDefaultVec2(0,0);
    acceleration = ofDefaultVec2(0,0);
    ofw = ofGetWindowWidth();
    ofh = ofGetWindowHeight();
}

particle::particle(glm::vec2 p, glm::vec2 v, glm::vec2 a)
{
    position = p;
    velocity = v;
    acceleration = a;
}

void particle::run() {

}

void particle::update() {
    velocity += acceleration;
    position += velocity;
}

void particle::display() {

}

bool particle::isDead() {
    return false;
}
