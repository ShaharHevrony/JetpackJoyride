#include "Bound.h"

Bound::Bound(b2World *world, int type) :Box2Object(world, type){
    create(world, b2_staticBody);
}

void Bound::create(b2World *world, b2BodyType bodyType) {
    //BodyDef
    b2BodyDef bodyDef;
    b2PolygonShape boxShape;
    bodyDef.type = bodyType;
    if (m_type == B2Floor) {  //If this bound is a floor then:
        bodyDef.position.Set(WIDTH_CENTER, WINDOW_HEIGHT);
        m_object.setPosition(WIDTH_CENTER, WINDOW_HEIGHT);
        boxShape.SetAsBox(WINDOW_WIDTH, FLOOR_POS_Y);
    } else {                  //If this bound in a ceiling then:
        bodyDef.position.Set(WIDTH_CENTER, 0.f);
        boxShape.SetAsBox(WINDOW_WIDTH, CEILING_POS_Y);
    }
    m_body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.isSensor = false;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.2f;
    m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);
}

void Bound::setChange(b2World *world) {
    b2BodyDef bodyDef;
    b2PolygonShape boxShape;

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(WIDTH_CENTER, WINDOW_HEIGHT);
    boxShape.SetAsBox(WINDOW_WIDTH, FLOOR_POS_Y);
    m_body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.isSensor = false;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = BERRYS_FRICTION;
    fixtureDef.friction = BERRYS_FRICTION;
    m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);
}

void Bound::draw(sf::RenderWindow* window) {
    auto angle = m_body->GetAngle() * 180 / b2_pi;
    m_object.setRotation(angle);
    m_object.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
    window->draw(m_object);
}