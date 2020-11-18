#include "particlesystem.h"


particleSystem::particleSystem()
{
    ofh = ofGetHeight();
    ofw = ofGetWidth();
    roboto32.load("Roboto-Medium.ttf",32,true,true);
}

void particleSystem::addDropParticle() {
    dropParticle dp(glm::vec2 (ofRandom(ofw),-10));
    dropParticles.push_back(dp);

}

void particleSystem::run(ofImage& canvasRef) {
    //println(particles.size());
    for (int i = dropParticles.size()-1; i >= 0; i--) {

    //returns status -- 0 ok, 1 touched body, 2 touched ground

      int result = dropParticles[i].run(canvasRef);
      if (dropParticles[i].isDead()) {
        dropParticles.erase(dropParticles.begin()+i); // needs to use an iterator here
      }
        //for debugging
        else {
          roboto32.drawString(std::to_string(i),dropParticles[i].position.x,dropParticles[i].position.y);
        }
      if (result==1) {
          //splash and slide
      }
    }

}
