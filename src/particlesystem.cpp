#include "particlesystem.h"


particleSystem::particleSystem()
{
    ofh = ofGetHeight();
    ofw = ofGetWidth();
    roboto.load("Roboto-Medium.ttf",32,true,true);
    aguaText = "agua";
}

void particleSystem::addDropParticle() {
    dropParticle dp(glm::vec2 (ofRandom(ofw),-10));
    dropParticles.push_back(dp);
}

void particleSystem::addSplashParticle(glm::vec2 touch_point) {
    splashParticle sp(touch_point);
    splashParticles.push_back(sp);
}

void particleSystem::addWordParticle(float x) {
    wordParticle wp(x,roboto,aguaText);
    wordParticles.push_back(wp);
}

void particleSystem::run(vector <ofPolyline> blobs){
    //println(particles.size());
    for (int i = dropParticles.size()-1; i >= 0; i--) {

    //returns status -- 0 ok, 1 touched body, 2 touched ground

      dropParticles[i].run(blobs);
      if (dropParticles[i].isDead()) {
          if (dropParticles[i].touch) {
              int splashes_amount = (int)ofRandom(4);
              for (int j=0;j<splashes_amount;j++)
                addSplashParticle(dropParticles[i].touch_point);
          } else {
              if (dropParticles[i].ground) {
                  addWordParticle(dropParticles[i].position.x);
              }
          }
        dropParticles.erase(dropParticles.begin()+i); // needs to use an iterator here
      }
    }

    for (int i = splashParticles.size()-1; i >= 0; i--) {
        splashParticles[i].run();
        if (splashParticles[i].isDead())
            splashParticles.erase(splashParticles.begin()+i);
    }

    for (int i = wordParticles.size()-1; i >= 0; i--) {
        wordParticles[i].run();
        if (wordParticles[i].isDead())
            wordParticles.erase(wordParticles.begin()+i);
    }

}
