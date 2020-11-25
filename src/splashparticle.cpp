#include "splashparticle.h"


splashParticle::splashParticle(glm::vec2 p) {

        position = p;
        acceleration = glm::vec2 (0,0.2);
        lifetime = 10;
        dead = false;

        int side = 1;
        speed = 2.5f;
        if (ofRandom(2) > 1)
          side = -1;
        float angle = ofRandom (0, PI/3); //between 30 and 60 degress

        velocity = glm::vec2(speed*cos(angle)*side, -speed*sin(angle));

}


void splashParticle::run() {

    update();
    if (!dead) display();

}

void splashParticle::update() {

    velocity += acceleration;
    position += velocity;
    lifetime--;



}
void splashParticle::display(){

    ofSetColor(ofColor::lightGray);
    ofDrawCircle(position,1);
}

bool splashParticle::isDead() {
    return dead;
}
