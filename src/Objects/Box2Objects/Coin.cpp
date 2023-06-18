#include "Coin.h"

Coin::Coin(sf::Texture* texture, const sf::Vector2f& position, b2World* world, float scale, int type)
                :Box2Object(texture, position, type), m_scale(scale) {
    setAnimate(ResourcesManager::instance().getCoin(), sf::Vector2u(8, 1), 0.1f);
    if (type == B2StaticCoin) {
        create(world, b2_staticBody);
    } else if (type == B2DynamicCoin) {
        m_object.setOrigin(m_object.getTexture()->getSize().x/2, m_object.getTexture()->getSize().y/2);
        create(world, b2_dynamicBody);
    }
}

//--------------- create the box2d values ---------------
void Coin::create(b2World *world, b2BodyType bodyType) {
    //BodyDef
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(m_object.getPosition().x, m_object.getPosition().y);
    bodyDef.angularDamping = OBJECT_SCALE;
    m_body = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_p.Set(0, 0);
    shape.m_radius = 0.1f;

    //FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.isSensor = false;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 1.f;
    fixtureDef.restitution = 1.f; //Add the restitution property
    m_body->CreateFixture(&fixtureDef);

    b2MassData mass;
    mass.center = m_body->GetLocalCenter();
    mass.mass = COINS_MASS * m_scale / 2;
    mass.I = m_object.getOrigin().y;
    m_body->SetMassData(&mass);

    m_body->SetFixedRotation(true);
    m_body->SetUserData(this);
    m_body->SetGravityScale(m_scale);
}

//-------------- handle all collisions --------------
void Coin::move(float time) {
    animate();
    if(m_body->GetType() == b2_dynamicBody) {
        b2Vec2 bodyVelocity = m_body->GetLinearVelocity();
        if(m_scale >= 4.f){
            bodyVelocity.x = -time * m_scale;
        } else {
            bodyVelocity.x = -4 * time * m_scale;
        }
        m_body->SetLinearVelocity(bodyVelocity);
        b2Vec2 bodyPosition = m_body->GetPosition();
        float bodyAngle = m_body->GetAngle();
        m_object.setPosition(bodyPosition.x, bodyPosition.y);
        m_object.setRotation(bodyAngle * 180.0f / b2_pi);
    } else if(m_body->GetType() == b2_staticBody) {
        sf::Vector2f direction(-1,0);
        m_object.move(direction*time);
    }
}

void Coin::draw(sf::RenderWindow* window) {
    if(m_body->GetType() == b2_dynamicBody) {
        auto angle = m_body->GetAngle() * 180.0f / b2_pi;
        m_object.setRotation(angle);
        m_object.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
    }
    window->draw(m_object);
}

void Coin::handleCollision(Object& object) {
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void Coin::handleCollision(Player& player) {
    player.handleCollision(*this);
}

void Coin::updateCollisionTime(float time) {
    if (m_collided) {
        m_collisionTime += time;
    }
    if ((m_collisionTime >= 0.1f && m_body->GetType() == b2_dynamicBody) || (m_collisionTime >= 0.3f && m_body->GetType() == b2_staticBody)) {
        m_isDelete = true;
    }
}