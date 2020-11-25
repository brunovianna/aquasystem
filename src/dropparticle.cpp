#include "dropparticle.h"


dropParticle::dropParticle():particle()
{
    reddish = ofColor(128,0,0);
    dead = false;

}

dropParticle::dropParticle(glm::vec2 p) {

    position = p;
    velocity = glm::vec2(ofRandom(5.0,6.0), 20. );
    acceleration = glm::vec2 (0,0.01);
    ofw = ofGetWindowWidth();
    ofh = ofGetWindowHeight();
    reddish = ofColor(106,0,0);
    dead = false;
    touch = false;
    touch_point = glm::vec2(-1.,-1.);


}

int dropParticle::run(vector <ofPolyline> blobs) {

    int result = update(blobs);
    if (!dead) display();
    return  result;;
}

int dropParticle::update(vector <ofPolyline> blobs) {
    //returns status -- 0 ok, 1 touched body, 2 touched ground

    int result = 0;
    velocity += acceleration;
    position += velocity;

    for (ofPolyline blob: blobs) {
        if (blob.inside(ofPoint(position))) {
            result = 1;
            touch = true;
            touch_point = blob.getClosestPoint(ofPoint(position));
        }
    }


    return result;
}
void dropParticle::display(){

    if (touch) {
        ofSetColor(ofColor::red);
        ofDrawCircle(touch_point,2);
        dead = true;
    } else {
        ofSetColor(ofColor::lightGray);
        float dropHead = 2.5;
        ofDrawEllipse(position.x, position.y, dropHead,dropHead*1.5);
        float dropLength = 3;
        glm::vec2 dropStart  ((position.x-dropLength*velocity.x), (position.y-dropLength*velocity.y));
        ofDrawLine (dropStart.x, dropStart.y, position.x, position.y); //todo : gradient from white in the bottom to gray in the top
    }
}

bool dropParticle::isDead() {
    return dead;
}
