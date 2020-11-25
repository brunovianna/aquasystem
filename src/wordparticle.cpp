#include "wordparticle.h"

wordParticle::wordParticle(float x, ofTrueTypeFont _font, string _text)
{

    text = _text;
    font = _font;
    float ofh = ofGetWindowHeight();
    font_rect = font.getStringBoundingBox(text, 0,0);
    position = glm::vec2(x-font_rect.width/2, ofh-font_rect.height/2);
    acceleration = glm::vec2 (0,0.2);
    dead = false;

    int side = 1;
    float speed = 2.5f;
    if (ofRandom(2) > 1)
      side = -1;
    float angle = ofRandom (0, PI/3); //between 30 and 60 degress

    velocity = glm::vec2(speed*cos(angle)*side, -speed*sin(angle));


}



void wordParticle::run() {

    update();
    if (!dead) display();

}

void wordParticle::update() {

    velocity += acceleration;
    position += velocity;
    if (position.y - font_rect.getHeight() > ofh)
        dead = true;

}
void wordParticle::display(){

    ofSetColor(ofColor::lightGray);
    font.drawString(text,position.x,position.y);
}

bool wordParticle::isDead() {
    return dead;
}
