
#include "TempPlayer.h"


TempPlayer::TempPlayer(sf::Texture *texture, sf::Vector2f position, std::unique_ptr<b2World>* world)
    : Object(texture, position) {
    create(world->get(),b2_dynamicBody,109);
    createSensor(world->get(), m_object.getGlobalBounds().height, 10, b2Vec2(0, m_object.getGlobalBounds().height), 1);
}

void TempPlayer::create(b2World *world,b2BodyType bodyType, float radius) {
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(m_object.getPosition().x, m_object.getPosition().y);
    m_body = world->CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_p.Set(0, 0);
    circle.m_radius = radius;

    // FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    if (bodyType == b2_dynamicBody) {
        fixtureDef.density = 0.3f;
        fixtureDef.friction = 0.3f;
    }
    m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);
}

void TempPlayer::createSensor(b2World *world, float width, float height, b2Vec2 center, int data) {
    b2PolygonShape shape;
    shape.SetAsBox(width, height, center, 0);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = 1.0f;
    fixture.friction = 0.1f;
    fixture.isSensor = true;
    m_body->CreateFixture(&fixture)->SetUserData((void *) data);
}

void TempPlayer::space(){
    float jumpVelocity = -30.0f; // Adjust the jump velocity as needed
    b2Vec2 bodyVelocity = m_body->GetLinearVelocity();
    bodyVelocity.y = jumpVelocity;
    m_body->SetLinearVelocity(bodyVelocity);
    b2Vec2 bodyPosition = m_body->GetPosition();
    float bodyAngle = m_body->GetAngle();
    m_object.setPosition(bodyPosition.x * SCALE, bodyPosition.y * SCALE);
    m_object.setRotation(bodyAngle * 180.0f / b2_pi);
}