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
void Player::create(b2World* world, b2BodyType bodyType) {
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(m_object.getPosition().x, m_object.getPosition().y);
    bodyDef.angularDamping = 1.f;
    m_body = world->CreateBody(&bodyDef); //Create the Box2D body in the specified world

    b2PolygonShape shape;
    shape.SetAsBox(m_object.getTextureRect().width / 8, m_object.getTextureRect().height / 8); //Set the shape of the Box2D body as a box

    //FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.isSensor = false;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.3f;
    fixtureDef.friction = FRICTION;
    m_body->CreateFixture(&fixtureDef); // Attach the fixture to the Box2D body

    b2MassData mass;
    mass.center = m_body->GetLocalCenter();
    mass.mass = MASS;
    mass.I = m_object.getOrigin().y;
    m_body->SetMassData(&mass);     //Set the mass properties of the Box2D body
    m_body->SetFixedRotation(true); //Prevent rotation of the Box2D body
    m_body->SetUserData(this);      //Set the user data of the Box2D body to 'this' (referring to the Player object)
}

//------------- SFML functions on window -------------
void Player::move(float time) {
    PlayerStateManager::instance().moveByPress();
    PlayerStateManager::instance().animateByState();
}

//-------------- handle all collisions --------------
void Player::handleCollision(Object& object) {
    if (&object != this) {
        object.handleCollision(*this); //Delegate collision handling to the collided object
    }
}

void Player::handleCollision(Laser& laser) {
    if (laser.getShape().getGlobalBounds().intersects(m_object.getGlobalBounds())) {
        //Collision between Player and Laser detected
        float obstacleTime = 0.7f;
        PlayerStateManager::instance().handleCollisionByState(obstacleTime); //Handle collision based on player state
        m_ZapperSound.play();                                                //Play the Zapper sound effect
    }
}

void Player::handleCollision(Beam& beam) {
    std::vector<sf::CircleShape> beamsCircles = beam.getCircles();
    for (auto circle : beamsCircles) {
        if (circle.getGlobalBounds().intersects(m_object.getGlobalBounds())) {
            //Collision between Player and Beam detected
            float beamTime = 1.f;
            PlayerStateManager::instance().handleCollisionByState(beamTime); //Handle collision based on player state
            m_ZapperSound.play();                                            //Play the Zapper sound effect
        }
    }
}

void Player::handleCollision(Piggy& piggy) {
    if (piggy.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds())) {
        //Collision between Player and Piggy detected
        piggy.setDelete(); //Mark the Piggy for deletion
        Event event = Event(CollectedPiggy, COLLECTED_PIGGY, piggy.getObject().getPosition());
        EventsQueue::instance().push(event); //Push an event to the event queue
        m_CoinCollect.play();                //Play the Coin Collect sound effect
    }
}

void Player::handleCollision(Coin& coin) {
    if (coin.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds()) && !coin.getCollided()) {
        //Collision between Player and Coin detected
        coin.setCollided(); //Mark the Coin as collided
        coin.setAnimate(ResourcesManager::instance().getGlitter(), sf::Vector2u(3, 1), 0.1f); //Set animation for the Coin
        Event event = Event(CollectedMoney, COLLECTED_MONEY);
        EventsQueue::instance().push(event); //Push an event to the event queue
        m_CoinCollect.play();                //Play the Coin Collect sound effect
    }
}

void Player::handleCollision(Missile& missile) {
    if (missile.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds())) {
        //Collision between Player and Missile detected
        missile.setDelete(); //Mark the Missile for deletion
        float missileTime = 0.f;
        PlayerStateManager::instance().handleCollisionByState(missileTime); //Handle collision based on player state
        m_soundHitMissile.play();                                           //Play the Missile hit sound effect
    }
}

void Player::handleCollision(SuperPower& SuperPower) {
    if (SuperPower.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds()) && !SuperPower.getCollided()) {
        //Collision between Player and SuperPower detected
        SuperPower.setCollided(); //Mark the SuperPower as collided
        SuperPower.setDelete();   //Mark the SuperPower for deletion
        Event event = Event(startSuperPower, COLLECTED_SUPER); //Create an event to start the SuperPower
        EventsQueue::instance().push(event);                   //Push the event to the event queue
        m_soundGetPowerBox.play();                             //Play the sound effect for collecting the SuperPower
    }
}
