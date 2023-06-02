#include "Player.h"
#include "Values.h"

Player::Player(sf::Texture *texture, sf::Vector2f position, std::unique_ptr<b2World>* world, int type)
                :Box2dObject(texture, position, world, type) {
    create(world->get());
}

//--------------- create the box2d values ---------------
void Player::create(b2World *world) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_object.getPosition().x, m_object.getPosition().y);
    bodyDef.linearDamping = 0.0f;
    bodyDef.angularDamping = 1.f;
    m_body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(m_object.getGlobalBounds().width/2, m_object.getGlobalBounds().height/2);

    //FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.3f;
    fixtureDef.friction = 0.3f;
    m_body->CreateFixture(&fixtureDef);

    b2MassData mass;
    mass.center = m_body->GetLocalCenter();
    mass.mass = BERRYS_MASS;
    mass.I = m_object.getOrigin().y;
    m_body->SetMassData(&mass);

    m_body->SetFixedRotation(true);
    m_body->SetUserData(this);
}

void Player::setDeath(b2World *world) {
    m_type = DeadPlayerType;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_object.getPosition().x, m_object.getPosition().y);
    bodyDef.linearDamping = 0.0f;
    bodyDef.angularDamping = 1.5f;
    m_body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(m_object.getGlobalBounds().width/2, m_object.getGlobalBounds().height/2);

    //FixtureDef
    b2FixtureDef objectFixtureDef;
    objectFixtureDef.shape = &shape;
    objectFixtureDef.density = BERRYS_FRICTION;
    objectFixtureDef.friction = BERRYS_FRICTION;
    objectFixtureDef.restitution = 0.8f;  // Add the restitution property
    m_body->CreateFixture(&objectFixtureDef);

    b2MassData mass;
    mass.center = m_body->GetLocalCenter();
    mass.mass = BERRYS_MASS;
    mass.I = m_object.getOrigin().y;
    m_body->SetMassData(&mass);

    m_body->SetFixedRotation(true);
    m_body->SetUserData(this);
}

//------------- SFML functions on window -------------
void Player::move(float time) {
    float length = m_object.getTexture()->getSize().x/4;
    if (m_type) {
        float jumpVelocity = - 10 * GRAVITATION_Y; //Adjust the jump velocity as needed
        b2Vec2 bodyVelocity = m_body->GetLinearVelocity();
        bodyVelocity.y = jumpVelocity;
        m_body->SetLinearVelocity(bodyVelocity);
        b2Vec2 bodyPosition = m_body->GetPosition();
        float bodyAngle = m_body->GetAngle();
        m_object.setTextureRect(sf::IntRect(length * 3, 0, length, m_object.getTexture()->getSize().y));
        m_object.setPosition(bodyPosition.x, bodyPosition.y);
        m_object.setRotation(bodyAngle * 180.0f / b2_pi);
    }
    else {
        m_object.setTextureRect(sf::IntRect(length * 2, 0, length, m_object.getTexture()->getSize().y));
    }
}

void Player::draw(sf::RenderWindow* window) {
    auto angle = m_body->GetAngle() * 180 / b2_pi;
    m_object.setRotation(angle);
    m_object.setPosition(sf::Vector2f(m_body->GetPosition().x,m_body->GetPosition().y));
    window->draw(m_object);
}

//-------------- handle all collisions --------------
void Player::handleCollision(Object& object) {
    if (&object == this) {
        return;
    }
    else {
        object.handleCollision(*this);
    }
}

void Player::handleCollision(Coin& Coins) {
    if (Coins.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds())) {
        Coins.setDelete();
        Event event = Event(CollectedMoney, COLLECTED_MONEY);
        EventsQueue::instance().push(event);
    }
}

void Player::handleCollision(Obstacle& obstacle) {
    if (obstacle.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds())) {
        obstacle.setCollided();
        Event event = Event(DeathInTheAir, 0);
        EventsQueue::instance().push(event);
    }
}
