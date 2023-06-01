#include "Bound.h"

Bound::Bound(std::unique_ptr<b2World>* world, bool floor) : Object() {
    m_floor = floor;
    create(world->get());
}
void Bound::create(b2World* world) {
    //BodyDef
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    b2PolygonShape boxShape;
    if (m_floor) {
        bodyDef.position.Set(WIDTH_CENTER, WINDOW_HEIGHT);
        boxShape.SetAsBox(WINDOW_WIDTH, PLAYER_POS_Y);
    }
    else {
        bodyDef.position.Set(WIDTH_CENTER, 0.f); //Here the diff
        boxShape.SetAsBox(WINDOW_WIDTH, -PLAYER_POS_Y/3); //Here the diff
    }
    m_body = world->CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.2f;
    m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);
}
void Bound::draw(sf::RenderWindow* window) {
    auto angle = m_body->GetAngle() * 180 / b2_pi;
    m_object.setRotation(angle);
    m_object.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
    window->draw(m_object);
}


