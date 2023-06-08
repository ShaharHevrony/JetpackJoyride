#include "Player.h"

Player::Player(sf::Texture *texture, sf::Vector2f position, b2World* world, int type)
        : Box2Object(texture, position, world, 1.f, type) {
    create(world);
}

//--------------- create the box2d values ---------------
void Player::create(b2World *world) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_object.getPosition().x, m_object.getPosition().y);
    bodyDef.angularDamping = 1.f;
    m_body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(m_object.getGlobalBounds().width/4, m_object.getGlobalBounds().height/4);

    //FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.isSensor = false;
    m_sensor = fixtureDef.isSensor;
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

void Player::setChange(b2World *world) {
    m_type = DeadPlayerType;
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_object.getPosition().x, m_object.getPosition().y);
    bodyDef.angularDamping = SET_OBJ_SCALE;
    m_body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(m_object.getGlobalBounds().width/2, m_object.getGlobalBounds().height/2);

    //FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.isSensor = false;
    m_sensor = fixtureDef.isSensor;
    fixtureDef.shape = &shape;
    fixtureDef.density = BERRYS_FRICTION;
    fixtureDef.friction = BERRYS_FRICTION;
    fixtureDef.restitution = SET_OBJ_SCALE/2; //Add the restitution property
    m_body->CreateFixture(&fixtureDef);

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
    if (m_spacePressed) {
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
    m_object.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
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

void Player::handleCollision(Player &player) {}

void Player::handleCollision(Coin& Coin) {
    if (Coin.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds()) && !Coin.getCollided()) {
        Coin.setCollided();
        Coin.setObject(ResourcesManager::instance().getGlitter(), sf::Vector2u(3, 1), 0.1f);
        Event event = Event(CollectedMoney, COLLECTED_MONEY);
        EventsQueue::instance().push(event);
    }
}

void Player::handleCollision(Obstacle& obstacle) {
    if (obstacle.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds()) && m_type == PlayerType) {
        Event event = Event(DeathInTheAir);
        EventsQueue::instance().push(event);
    }
}

void Player::handleCollision(Beam &beam) {
    if (beam.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds())) {
        Event event = Event(DeathInTheAir);
        EventsQueue::instance().push(event);
    }
}

void Player::handleCollision(Piggy& piggy) {
    if (piggy.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds())) {
        piggy.setDelete();
        Event event = Event(CollectedPiggy, 0, piggy.getObject().getPosition());
        EventsQueue::instance().push(event);
    }
}

void Player::handleCollision (Box2Coin& box2Coin) {
    if (box2Coin.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds()) && !box2Coin.getCollided()) {
        box2Coin.setCollided();
        box2Coin.setObject(ResourcesManager::instance().getGlitter(), sf::Vector2u(3, 1), 0.1f);
        Event event = Event(CollectedMoney, COLLECTED_MONEY);
        EventsQueue::instance().push(event);
    }
}

void Player::handleCollision(Missile &missile) {
    if (missile.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds()) && m_type == PlayerType) {
        Event event = Event(DeathInTheAir);
        EventsQueue::instance().push(event);
    }
}