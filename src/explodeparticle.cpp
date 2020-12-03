#include "explodeparticle.h"


explodeParticle::explodeParticle(glm::vec2 _pos, ofTrueTypeFont _font, string _text)
{
    text = _text;
    font = _font;
    font_rect = font.getStringBoundingBox(text, 0,0);
    position = glm::vec2(_pos.x-font_rect.width/2, _pos.y-font_rect.height/2);
    acceleration = glm::vec2 (0,0.05);
    dead = false;

    int side = 1;
    float speed = 0.5f;
    if (ofRandom(2) > 1)
      side = -1;
    float angle = ofRandom (0, PI/3); //between 30 and 60 degress

    velocity = glm::vec2(speed*cos(angle)*side, -speed*sin(angle));

    life_time = 240;
}




void explodeParticle::run() {

    update();
    if (!dead) display();

}

void explodeParticle::update() {

    velocity += acceleration;
    position += velocity;
    life_time-=2;
    if ((position.y - font_rect.getHeight() > ofh)||(life_time==0))
        dead = true;

}
void explodeParticle::display(){

    ofSetColor(ofColor::lightBlue,life_time);
    font.drawString(text,position.x,position.y);

}

bool explodeParticle::isDead() {
    return dead;
}
