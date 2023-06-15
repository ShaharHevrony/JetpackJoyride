#include "Player.h"

Player::Player(sf::Texture *texture, sf::Vector2f position, b2World* world, int type) :Box2Object(texture, position, type) {
    create(world, b2_dynamicBody);
    m_CoinCollect.setBuffer(ResourcesManager::instance().getSoundCoin());
    m_ZapperSound.setBuffer(ResourcesManager::instance().getSoundZapper());
    m_soundHitMissile.setBuffer(ResourcesManager::instance().getSoundMissileHit());
    m_soundGetPowerBox.setBuffer(ResourcesManager::instance().getSoundPowerBox());

    //Set the volume of the sound object
    m_CoinCollect.setVolume(GameManager::instance().getSound());
    m_ZapperSound.setVolume(GameManager::instance().getSound());
    m_soundHitMissile.setVolume(GameManager::instance().getSound());
    m_soundGetPowerBox.setVolume(GameManager::instance().getSound());
}

//--------------- create the box2d values ---------------
void Player::create(b2World *world, b2BodyType bodyType) {
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(m_object.getPosition().x, m_object.getPosition().y);
    bodyDef.angularDamping = 1.f;
    m_body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(m_object.getGlobalBounds().width/8, m_object.getGlobalBounds().height/8);

    //FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.isSensor = false;
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
    m_object.setScale(PLAYER_SCALE,PLAYER_SCALE);
}

//------------- SFML functions on window -------------
void Player::move(float time) {
    PlayerStateManager::instance().moveByPress();
    PlayerStateManager::instance().moveByState();
}

void Player::draw(sf::RenderWindow* window) {
    auto angle = m_body->GetAngle() * 180 / b2_pi;
    m_object.setRotation(angle);
    m_object.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
    window->draw(m_object);
}

//-------------- handle all collisions --------------
void Player::handleCollision(Object& object) {
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void Player::handleCollision(Player &player) {}

void Player::handleCollision(Laser& laser) {
    if (laser.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds())) {
        float obstacleTime = 0.7f;
        PlayerStateManager::instance().handleCollisionByState(obstacleTime);
        m_ZapperSound.play();
    }
}

void Player::handleCollision(Beam &beam) {
    std::vector<sf::CircleShape> beamsCircles = beam.getCircles();
    for(auto circle : beamsCircles){
        if(circle.getGlobalBounds().intersects(m_object.getGlobalBounds())){
            float beamTime = 1.f;
            PlayerStateManager::instance().handleCollisionByState(beamTime);
            m_ZapperSound.play();
        }
    }
}

void Player::handleCollision(Piggy& piggy) {
    if (piggy.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds())) {
        piggy.setDelete();
        Event event = Event(CollectedPiggy, 0, piggy.getObject().getPosition());
        EventsQueue::instance().push(event);
        m_CoinCollect.play();
    }

}

void Player::handleCollision (Coin& coin) {
    if (coin.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds()) && !coin.getCollided()) {
        coin.setCollided();
        coin.setAnimate(ResourcesManager::instance().getGlitter(), sf::Vector2u(3, 1), 0.1f);
        Event event = Event(CollectedMoney, COLLECTED_MONEY);
        EventsQueue::instance().push(event);
        m_CoinCollect.play();
    }
}

void Player::handleCollision(Missile &missile) {
    if (missile.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds())){
        missile.setDelete();
        float missileTime = 0.f;
        PlayerStateManager::instance().handleCollisionByState(missileTime);
        m_soundHitMissile.play();
    }
}

void Player::handleCollision(SuperPower& SuperPower) {
    if (SuperPower.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds()) && !SuperPower.getCollided()) {
        SuperPower.setCollided();
        SuperPower.setDelete();
        Event event = Event(startSuperPower);
        EventsQueue::instance().push(event);
        m_soundGetPowerBox.play();
    }
}
