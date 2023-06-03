#include "Bound.h"

Bound::Bound(std::unique_ptr<b2World>* world, int type) : Box2dObject(world, type) {
    create(world->get());
}

void Bound::create(b2World *world) {
    //BodyDef
    b2BodyDef bodyDef;
    b2PolygonShape boxShape;

    bodyDef.type = b2_staticBody;
    if (m_type == FloorType) {  //If this bound is a floor then:
        bodyDef.position.Set(WIDTH_CENTER, WINDOW_HEIGHT);
        m_object.setPosition(WIDTH_CENTER, WINDOW_HEIGHT);
        boxShape.SetAsBox(WINDOW_WIDTH, PLAYER_POS_Y * 1.5);
    }
    else {                      //If this bound in a ceiling then:
        bodyDef.position.Set(WIDTH_CENTER, 0.f);
        boxShape.SetAsBox(WINDOW_WIDTH, PLAYER_POS_Y * 0.1);
    }
    m_body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.2f;
    m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);
}

void Bound::setDeath(b2World* world) {
    b2BodyDef bodyDef;
    b2PolygonShape boxShape;

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(WIDTH_CENTER, WINDOW_HEIGHT);
    boxShape.SetAsBox(WINDOW_WIDTH, PLAYER_POS_Y * 1.5);
    m_body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
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