#include "dropparticle.h"



dropParticle::dropParticle(glm::vec2 p,  glm::vec2 v,  ofImage &di) {

    position = p;
    velocity = v;
    angle = atan(velocity.y/velocity.x) - PI/2;
    acceleration = glm::vec2 (0,0.01);
    ofw = ofGetWindowWidth();
    ofh = ofGetWindowHeight();

    dead = false;
    touch = false;
    ground = false;
    explode = false;
    touch_point = glm::vec2(-1.,-1.);
    drop_image = di;

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
        //using blobs from of
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

        // using shapes from box2d
        // doesn't work, missing the function to find the closes
//        b2Vec2 points[3];
//        for (auto shape: polyShapes)
//        {
//            for (auto t: shape->triangles)
//            {
//                b2Transform transform;
//                transform.SetIdentity();
//                b2Vec2 point(position.x, position.y);

//                points[0].Set( t.a.x,t.a.y);
//                points[1].Set( t.b.x,t.b.y);
//                points[2].Set( t.c.x,t.c.y);

//                b2PolygonShape bs;
//                bs.Set(points,3);

//                if (bs.TestPoint(transform, point))
//                {

//                    dead = true;
//                    float32 distance = 0;
//                    b2Vec2 normal = b2Vec2();
//                    bs.ComputeDistance(transform,point,&distance,&normal,0);
//                    if (distance>20.0)
//                    {
//                        explode = true;
//                    } else {
//                        touch = true;
//                    }
//                }
//            }
//        }
    }

}
void dropParticle::display(){


    //drop "head"
//    int drop_steps = 10;
//    float start_gray = 200;
//    for (int i=0;i<drop_steps;i++)
//    {

//        ofSetColor(ofMap(i,0,drop_steps,start_gray,0));
//        ofDrawCircle(position.x-i*velocity.x*0.2, position.y-i*velocity.y*0.2,ofMap(i,0,drop_steps,2.5,0));
//    }


    // drop line
//    int drop_line_length = 30;
//    for (int i=0;i<drop_line_length;i++)
//    {

//        ofSetColor(ofMap(i,0,drop_line_length,start_gray,0));
//        ofDrawCircle(position.x-i*velocity.x*0.1, position.y-i*velocity.y*0.1,1.f);
//    }


//    ofSetColor(ofColor::lightGray);
//    float dropHead = 2.5;
//    ofDrawEllipse(position.x, position.y, dropHead,dropHead*2.5);
//    float dropLength = 3;
//    glm::vec2 dropStart  ((position.x-dropLength*velocity.x), (position.y-dropLength*velocity.y));
//    ofDrawLine (dropStart.x, dropStart.y, position.x, position.y); //todo : gradient from white in the bottom to gray in the top


    ofSetColor(ofColor::lightGray);
    ofEnableAntiAliasing();

    drop_image.draw(100,100);

    ofPushMatrix();
    ofTranslate(position.x, position.y);
    ofRotateRad(angle);
    drop_image.draw(-drop_image.getWidth()/2,-drop_image.getHeight());
    ofPopMatrix();
//    drop_image.draw(position.x-drop_image.getWidth()/2, position.y-drop_image.getHeight());



}

bool dropParticle::isDead() {
    return dead;
}
