#include "Player.h"
#include "Values.h"

Player::Player(sf::Texture *texture, sf::Vector2f position, std::unique_ptr<b2World>* world) : Object(texture, position) {
    create(world->get());
}

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
    m_body->SetFixedRotation(true);
    m_body->SetUserData(this);
}

void Player::setDeath(b2World *world) {
    m_death = true;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_object.getPosition().x, m_object.getPosition().y);
    //bodyDef.linearDamping = 0.0f;
    //bodyDef.angularDamping = 0.0f;
    m_body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(m_object.getGlobalBounds().width/2, m_object.getGlobalBounds().height/2);

    //FixtureDef
    b2FixtureDef objectFixtureDef;
    objectFixtureDef.shape = &shape;
    objectFixtureDef.density = 0.1f;
    objectFixtureDef.friction = 100.f;
    objectFixtureDef.restitution = 2.f;  // Add the restitution property
    m_body->CreateFixture(&objectFixtureDef);
    m_body->SetFixedRotation(true);
    m_body->SetUserData(this);
}

void Player::draw(sf::RenderWindow* window) {
    auto angle = m_body->GetAngle() * 180 / b2_pi;
    m_object.setRotation(angle);
    m_object.setPosition(sf::Vector2f(m_body->GetPosition().x,m_body->GetPosition().y));
    window->draw(m_object);
}

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

void Player::playAnimationOnce(sf::Texture* tempTex) {
    if (!m_animation.hasPlayed()) {
        // Set the switch time to control the animation speed
        float switchTime = 0.18f;
        m_animation = Animation(tempTex, sf::Vector2u(3, 1), switchTime);
    }
}

void Player::handleCollision(Obstacle& obstacle) {
    if (obstacle.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds())) {
        obstacle.setCollided();
        Event event = Event(Death, 0);
        EventsQueue::instance().push(event);
    }
}

void Player::moveRightDown() {
    float jumpVelocityX = 10.0f; // Adjust the horizontal jump velocity as needed
    float jumpVelocityY = 10.0f; // Adjust the vertical jump velocity as needed
    b2Vec2 bodyVelocity = m_body->GetLinearVelocity();
    bodyVelocity.x = jumpVelocityX;
    bodyVelocity.y = jumpVelocityY;
    m_body->SetLinearVelocity(bodyVelocity);
}

void Player::move(float time) {
    float length = m_object.getTexture()->getSize().x/4;
    if (m_space) {
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
void Player::setSpace(bool set) {
    m_space = set;
}

bool Player::getSpace() const{
    return m_space;
}

bool Player::getDeathStat() const {
    return m_death;
}