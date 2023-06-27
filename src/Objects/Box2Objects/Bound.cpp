#include "Bound.h"

Bound::Bound(b2World *world, int type) :Box2Object(type){
    create(world, b2_staticBody);
}

//--------------- create the box2d values ---------------
void Bound::create(b2World *world, b2BodyType bodyType){
    //BodyDef
    b2BodyDef bodyDef;
    b2PolygonShape boxShape;
    bodyDef.type = bodyType;
    if (m_type == B2Floor) {        //If this bound is a floor then:
        bodyDef.position.Set(WIDTH_CENTER, WINDOW_HEIGHT);
        boxShape.SetAsBox(WINDOW_WIDTH, FLOOR_POS_Y);
        m_object.setPosition(WIDTH_CENTER, WINDOW_HEIGHT);
    } else {                        //If this bound in a ceiling then:
        bodyDef.position.Set(WIDTH_CENTER, 0.f);
        boxShape.SetAsBox(WINDOW_WIDTH, CEILING_POS_Y);
        m_object.setPosition(WIDTH_CENTER, 0.f);
    }
    m_body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.isSensor = false;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = BERRYS_FRICTION;
    fixtureDef.friction = BERRYS_FRICTION;
    m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);
}

void Bound::handleCollision(Object &object) {
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void Bound::handleCollision(Player& player) {
    player.handleCollision(*this);
}
