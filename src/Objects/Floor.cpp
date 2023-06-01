#include "Floor.h"

Floor::Floor(std::unique_ptr<b2World> *world) : Object(){
    create(world->get());
}

void Floor::create(b2World *world) {
    //BodyDef
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    b2PolygonShape boxShape;

    bodyDef.position.Set(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
    boxShape.SetAsBox(WINDOW_WIDTH,120.f);
    m_body = world->CreateBody(&bodyDef);

    // FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.2f;
    m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);
}

void Floor::draw(sf::RenderWindow *window) {
    auto angle = m_body->GetAngle() * 180 / b2_pi;
    m_object.setRotation(angle);
    m_object.setPosition(sf::Vector2f(m_body->GetPosition().x,m_body->GetPosition().y));
    window->draw(m_object);
}

Ceiling::Ceiling(std::unique_ptr<b2World> *world) : Object(){
    create(world->get());
}

void Ceiling::create(b2World *world) {
    //BodyDef
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(WINDOW_WIDTH / 2, 0.f);//here the diff

    b2PolygonShape boxShape;
    boxShape.SetAsBox(WINDOW_WIDTH, -40.f);//here the diff
    m_body = world->CreateBody(&bodyDef);

    // FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.2f;
    m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);
}

void Ceiling::draw(sf::RenderWindow *window) {
    auto angle = m_body->GetAngle() * 180 / b2_pi;
    m_object.setRotation(angle);
    m_object.setPosition(sf::Vector2f(m_body->GetPosition().x,m_body->GetPosition().y));
    window->draw(m_object);
}