#include "dropparticle.h"


dropParticle::dropParticle():particle()
{
    reddish = ofColor(128,0,0);
    dead = false;

}

dropParticle::dropParticle(glm::vec2 p) {

    position = p;
    velocity = glm::vec2(1.5, ofRandom(5.0,6.0));
    acceleration = glm::vec2 (0,0.005);
    ofw = ofGetWindowWidth();
    ofh = ofGetWindowHeight();
    reddish = ofColor(106,0,0);
    dead = false;


}

int dropParticle::run(ofImage& canvasRef) {

    int result = update(canvasRef);
    if (!dead) display();
    return  result;;
}

int dropParticle::update(ofImage& canvasRef) {
    //returns status -- 0 ok, 1 touched body, 2 touched ground

    int result = 0;
    velocity += acceleration;
    position += velocity;

    ofPixels pixels = canvasRef.getPixels();

    int pixelIndex = int(position.y)*ofw*4+int(position.x)*4;
        //BGRA
        if ((pixelIndex >=0) && (pixelIndex < ofw*ofh*4)) {
          if ((pixels[pixelIndex]==reddish.b)&&(pixels[pixelIndex+1]==reddish.g)&&(pixels[pixelIndex+2]==reddish.r)) {
            result = 1;
            dead = true;
          }
        } else {
          if (position.y > ofw) {
            if (ofRandom(10)>6) {
              // TODO make word
                result = 2;
              //ps.addWordParticle(position);
              dead = true;
            }
          }
        }

    return result;
}
void dropParticle::display(){

    ofSetColor(ofColor::lightGray);
    float dropHead = 2.5;
    ofDrawEllipse(position.x, position.y, dropHead,dropHead*1.5);
    float dropLength = 10;
    glm::vec2 dropStart  ((position.x-dropLength*velocity.x), (position.y-dropLength*velocity.y));
    ofDrawLine (dropStart.x, dropStart.y, position.x, position.y); //todo : gradient from white in the bottom to gray in the top

}

bool dropParticle::isDead() {
    return dead;
}
