#ifndef EXPLODEPARTICLE_H
#define EXPLODEPARTICLE_H

#include "particle.h"

class explodeParticle : public particle
{
public:
    explodeParticle(glm::vec2 _pos, ofTrueTypeFont _font, string _text);
    void display();
    void run();
    void update();
    bool isDead();

    string text;
    ofTrueTypeFont	font;
    ofRectangle font_rect;
    int life_time;

};

#endif // EXPLODEPARTICLE_H
