#include "Coin.h"

Coin::Coin(sf::Texture* texture, const sf::Vector2f& position, b2World* world, float scale, int type)
        :Box2Object(texture, position, type), m_scale(scale) {
    setAnimate(ResourcesManager::instance().getCoin(), sf::Vector2u(BUTTON_NUM, FIRST), ZERO_POINT_ONE);
    if (type == B2StaticCoin) {
        create(world, b2_staticBody);
    } else if (type == B2DynamicCoin) {
        m_object.setOrigin(m_object.getTextureRect().width/DIV_TWO, m_object.getTextureRect().height);
        create(world, b2_dynamicBody);
    }
}

void Coin::create(b2World* world, b2BodyType bodyType) {
    //Function to create the Box2D body for the coin
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(m_object.getPosition().x, m_object.getPosition().y);
    bodyDef.angularDamping = OBJECT_SCALE;
    m_body = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_p.Set(ZERO, ZERO);
    shape.m_radius = ZERO_POINT_ONE;

    //FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.isSensor = false;
    fixtureDef.shape = &shape;
    fixtureDef.density = ZERO_POINT_FIVE;
    fixtureDef.friction = FRICTION;
    fixtureDef.restitution = ONE_POINT_ZERO; //Add the restitution property
    m_body->CreateFixture(&fixtureDef);

    b2MassData mass;
    mass.center = m_body->GetLocalCenter();
    mass.mass = MASS * m_scale;
    mass.I = m_object.getOrigin().y;
    m_body->SetMassData(&mass);

    m_body->SetFixedRotation(true);
    m_body->SetUserData(this);
    m_body->SetGravityScale(m_scale);
}

void Coin::move(float time) {
    //Function to handle coin movement
    if (m_body->GetType() == b2_dynamicBody) {
        b2Vec2 bodyVelocity = m_body->GetLinearVelocity();
        if (m_scale >= FOUR_F) {
            bodyVelocity.x = -time * m_scale;
        } else {
            bodyVelocity.x = -FOUR * time * m_scale;
        }
        m_body->SetLinearVelocity(bodyVelocity);
        b2Vec2 bodyPosition = m_body->GetPosition();
        float bodyAngle = m_body->GetAngle();
        m_object.setPosition(bodyPosition.x, bodyPosition.y);
        m_object.setRotation(bodyAngle * ANGLE_CALC);
    } else {
        m_object.move(DIRECTION * time);
    }
}

void Coin::updateCollisionTime(float time) {
    //Function to update collision time and check if the coin should be deleted
    if (m_collided) {
        m_collisionTime += time;
    }
    if ((m_collisionTime >= 0.1f && m_body->GetType() == b2_dynamicBody) || (m_collisionTime >= ZERO_POINT_THREE && m_body->GetType() == b2_staticBody)) {
        m_isDelete = true;
    }
}

void Coin::handleCollision(Object& object) {
    //Function to handle collision with another object
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void Coin::handleCollision(Player& player) {
    player.handleCollision(*this);
}