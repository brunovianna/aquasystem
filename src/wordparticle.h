#ifndef WORDPARTICLE_H
#define WORDPARTICLE_H

#include "particle.h"

class wordParticle : public particle
{
public:
    wordParticle(float x, ofTrueTypeFont _font, string _text);
    void display();
    void run();
    void update();
    bool isDead();

    string text;
    ofTrueTypeFont	font;
    ofRectangle font_rect;

};

#endif // WORDPARTICLE_H
