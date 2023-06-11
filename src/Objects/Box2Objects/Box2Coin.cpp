#include "Box2Coin.h"

Box2Coin::Box2Coin(sf::Texture* texture, const sf::Vector2f& position, b2World* world, float scale, int type)
                :Box2Object(texture, position, world, scale, type){
    create(world);
}

//--------------- create the box2d values ---------------
void Box2Coin::create(b2World *world) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_object.getPosition().x, m_object.getPosition().y);
    bodyDef.angularDamping = OBJECT_SCALE;
    m_body = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_p.Set(0, 0);
    shape.m_radius = 1.f;
    //FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.isSensor = false;
    m_sensor = fixtureDef.isSensor;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 1.1f;
    fixtureDef.restitution = 1.1f; //Add the restitution property
    m_body->CreateFixture(&fixtureDef);

    b2MassData mass;
    mass.center = m_body->GetLocalCenter();
    mass.mass = COINS_MASS * m_scale;
    mass.I = m_object.getOrigin().y;
    m_body->SetMassData(&mass);

    m_body->SetFixedRotation(true);
    m_body->SetUserData(this);
    m_body->SetGravityScale(m_scale/50);
}

//-------------- handle all collisions --------------
void Box2Coin::move(float time) {
    animate();
    float length = m_object.getTexture()->getSize().x/4;
    b2Vec2 bodyVelocity = m_body->GetLinearVelocity();
    bodyVelocity.x = - m_scale/20;
    m_body->SetLinearVelocity(bodyVelocity);
    b2Vec2 bodyPosition = m_body->GetPosition();
    float bodyAngle = m_body->GetAngle();
    m_object.setTextureRect(sf::IntRect(length * 3, 0, length, m_object.getTexture()->getSize().y));
    m_object.setPosition(bodyPosition.x, bodyPosition.y);
    m_object.setRotation(bodyAngle * 180.0f / b2_pi);
}

void Box2Coin::draw(sf::RenderWindow* window) {
    auto angle = m_body->GetAngle() * 180 / b2_pi;
    m_object.setRotation(angle);
    m_object.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
    window->draw(m_object);
}

void Box2Coin::handleCollision(Object &object) {
    if (&object == this) {
        return;
    }
    else {
        object.handleCollision(*this);
    }
}

void Box2Coin::handleCollision(Player &player) {
    player.handleCollision(*this);
}

void Box2Coin::handleCollision(Box2Coin &box2Coin) {}

void Box2Coin::updateCollisionTime(float time) {
    if (m_collided) {
        m_collisionTime += time;
    }
    if (m_collisionTime >= 0.1f) {
        m_isDelete = true;
    }
}