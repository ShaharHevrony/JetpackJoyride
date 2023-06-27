#include "Bound.h"

Bound::Bound(b2World* world, int type)
    : Box2Object(type) {
    // Constructor for Bound with world and type parameters
    create(world, b2_staticBody);
}

void Bound::create(b2World* world, b2BodyType bodyType) {
    // Function to create the Box2D values for the Bound object
    b2BodyDef bodyDef;
    b2PolygonShape boxShape;
    bodyDef.type = bodyType;

    if (m_type == B2Floor) {
        // If this bound is a floor
        bodyDef.position.Set(WIDTH_CENTER, WINDOW_HEIGHT);
        boxShape.SetAsBox(WINDOW_WIDTH, FLOOR_POS_X);
        m_object.setPosition(WIDTH_CENTER, WINDOW_HEIGHT);
    }
    else {
        // If this bound is a ceiling
        bodyDef.position.Set(WIDTH_CENTER, 0.f);
        boxShape.SetAsBox(WINDOW_WIDTH, CEILING_POS_X);
        m_object.setPosition(WIDTH_CENTER, 0.f);
    }
    m_body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.isSensor = false;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = FRICTION;
    fixtureDef.friction = FRICTION;
    m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);
}

void Bound::handleCollision(Object& object) {
    // Function to handle collision with another object
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void Bound::handleCollision(Player& player) {
    // Function to handle collision with a Player object
    player.handleCollision(*this);
}
