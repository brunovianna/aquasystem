#include "dropparticle.h"



dropParticle::dropParticle(glm::vec2 p) {

    position = p;
    velocity = glm::vec2(ofRandom(5.0,6.0), 20. );
    acceleration = glm::vec2 (0,0.01);
    ofw = ofGetWindowWidth();
    ofh = ofGetWindowHeight();

    dead = false;
    touch = false;
    ground = false;
    explode = false;
    touch_point = glm::vec2(-1.,-1.);


}

void dropParticle::run(vector <ofPolyline> blobs) {

    update(blobs);
    if (!dead) display();
}

void dropParticle::update(vector <ofPolyline> blobs) {

    velocity += acceleration;
    position += velocity;

    if (position.y > ofh) {
        dead = true;
        ground = true;
    } else {
        for (ofPolyline blob: blobs) {
            if (blob.inside(ofPoint(position))) {
                dead = true;
                touch_point = blob.getClosestPoint(ofPoint(position));
                if (ofDist(touch_point.x,touch_point.y,position.x, position.y)>20.0) {
                    explode = true;
                } else {
                    touch = true;
                }

            }
        }
    }

}
void dropParticle::display(){

    //drop "head"
    int drop_steps = 10;
    float start_gray = 200;
    for (int i=0;i<drop_steps;i++)
    {

        ofSetColor(ofMap(i,0,drop_steps,start_gray,0));
        ofDrawCircle(position.x-i*velocity.x*0.2, position.y-i*velocity.y*0.2,ofMap(i,0,drop_steps,2.5,0));
    }


    // drop line
//    int drop_line_length = 30;
//    for (int i=0;i<drop_line_length;i++)
//    {

//        ofSetColor(ofMap(i,0,drop_line_length,start_gray,0));
//        ofDrawCircle(position.x-i*velocity.x*0.1, position.y-i*velocity.y*0.1,1.f);
//    }


    ofSetColor(ofColor::lightGray);
    float dropHead = 2.5;
    ofDrawEllipse(position.x, position.y, dropHead,dropHead*2.5);
    float dropLength = 3;
    glm::vec2 dropStart  ((position.x-dropLength*velocity.x), (position.y-dropLength*velocity.y));
    ofDrawLine (dropStart.x, dropStart.y, position.x, position.y); //todo : gradient from white in the bottom to gray in the top
}

bool dropParticle::isDead() {
    return dead;
}
