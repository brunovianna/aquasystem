#include "particlesystem.h"


particleSystem::particleSystem()
{
    ofh = ofGetHeight();
    ofw = ofGetWidth();
    roboto.load("Roboto-Medium.ttf",32,true,true);
    agua_text = "agua";
    explosion_text = "agua es vida";
    water_particles = NULL;
    water_particles_group = NULL;

    water_pd.flags = b2ParticleFlag::b2_waterParticle;
    water_pd.color = b2ParticleColor(161,200,226,70);
    water_pd.lifetime = 1000;


}

void particleSystem::addDropParticle() {
    dropParticle dp(glm::vec2 (ofRandom(ofw),-10));
    dropParticles.push_back(dp);
}

void particleSystem::addSplashParticle(glm::vec2 touch_point) {
    splashParticle sp(touch_point);
    splashParticles.push_back(sp);
}

void particleSystem::addWaterParticle(glm::vec2 create_point) {
    if ((water_particles!=NULL)&&(water_particles_group !=NULL))
    {
        ofVec2f position = create_point;
        ofVec2f velocity = ofVec2f(ofRandom(-10, 10), ofRandom(-20, -15));
        water_pd.position = ( b2Vec2 (position.x,position.y));
        water_pd.velocity = ( b2Vec2 (velocity.x,velocity.y));
        water_pd.group = water_particles_group;
//        water_particles->particleSystem->CreateParticle(water_pd);
      water_particles->createParticle(position, velocity);



    }
}


void particleSystem::addWordParticle(float x) {
    wordParticle wp(x,roboto,agua_text);
    wordParticles.push_back(wp);
}

void particleSystem::addExplodeParticle(glm::vec2 _pos, ofTrueTypeFont _font, string _text) {
    explodeParticle ep(_pos,_font,_text);
    explodeParticles.push_back(ep);
}

void particleSystem::run(vector <ofPolyline> blobs){
    //println(particles.size());
    for (int i = dropParticles.size()-1; i >= 0; i--) {

    //returns status -- 0 ok, 1 touched body, 2 touched ground

      dropParticles[i].run(blobs);
      if (dropParticles[i].isDead()) {
          if (dropParticles[i].touch) {
              int splashes_amount = (int)ofRandom(8);
              for (int j=0;j<splashes_amount;j++)
              {
                  addSplashParticle(dropParticles[i].touch_point);
                  addWaterParticle(glm::vec2 (dropParticles[i].touch_point.x,dropParticles[i].touch_point.y-7));
              }
          } else {
              if (dropParticles[i].ground) {
                  if (blobs.size()==0) { //only turn to word if no one is on camera
                      addWordParticle(dropParticles[i].position.x);
                  }
              } else {
                  if (dropParticles[i].explode) {
                      ofSetColor(ofColor::rosyBrown);
                      addExplodeParticle( dropParticles[i].position, roboto, explosion_text);
                      ofSetColor(ofColor::lightGray);
                  }
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

    for (int i = explodeParticles.size()-1; i >= 0; i--) {
        explodeParticles[i].run();
        if (explodeParticles[i].isDead())
            explodeParticles.erase(explodeParticles.begin()+i);
    }

    draw_circles(water_particles);
}

void particleSystem::draw_circles(ofxBox2dParticleSystem * water_particles)
{
    for (int i=0;i<water_particles->getParticleCount();i++)
    {



        ofSetColor(water_particles->color);
        ofEnablePointSprites();
        ofPushMatrix();
        ofScale(OFX_BOX2D_SCALE, OFX_BOX2D_SCALE);
        ofDrawCircle(water_particles->particleSystem->GetPositionBuffer()[i].x,water_particles->particleSystem->GetPositionBuffer()[i].y,water_particles->particleSystem->GetRadius());
        ofPopMatrix();
        ofDisablePointSprites();

    }
}
