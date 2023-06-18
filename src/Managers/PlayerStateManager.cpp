#include "PlayerStateManager.h"

PlayerStateManager::PlayerStateManager() {
    m_state = Regular;
    m_wasSuper = false;
    m_playerCollisionTime.restart();
}

PlayerStateManager& PlayerStateManager::instance() {
    try {
        static PlayerStateManager m_instance;
        return m_instance;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        throw;
    }
}

PlayerStateManager::~PlayerStateManager() {}

void PlayerStateManager::setPlayer(std::shared_ptr<Box2Object> player) {
    m_player = player;
    m_state  = Regular;
}

void PlayerStateManager::setState(int state, b2World* m_world) {
    m_state = state;
    switch (m_state) {
        case Regular: {
            m_player->setAnimate(ResourcesManager::instance().getPlayer(), sf::Vector2u(4, 1), 0.18f);
            b2Vec2 deathGravity(GRAVITATION_X, GRAVITATION_Y);
            m_world->SetGravity(deathGravity);
            m_player->getObject().setOrigin(m_player->getObject().getTextureRect().width/2, m_player->getObject().getTextureRect().height/2);
            break;
        }
        case SuperPowerTank: {
            m_player->setAnimate(ResourcesManager::instance().getSuperPower(1), sf::Vector2u(2, 1), 0.2f);
            b2Vec2 deathGravity(GRAVITATION_X, GRAVITATION_Y);
            m_world->SetGravity(deathGravity);
            m_player->getObject().setOrigin(m_player->getObject().getTextureRect().width/2, m_player->getObject().getTextureRect().height/2);
            break;
        }
        case SuperPowerRunner: {
            m_player->setAnimate(ResourcesManager::instance().getSuperPowerRunner(), sf::Vector2u(4, 1), 0.18f);
            m_player->getObject().setRotation(180.f);
            b2Vec2 deathGravity(- GRAVITATION_X, - GRAVITATION_Y);
            m_world->SetGravity(deathGravity);
            m_player->getObject().setOrigin(m_player->getObject().getTextureRect().width/2, m_player->getObject().getTextureRect().height/2);
            break;
        }
        case DeadPlayer: {
            m_player->setAnimate(ResourcesManager::instance().getBarryDeath(0), sf::Vector2u(4, 1), 0.18f);
            b2Vec2 deathGravity(DEATH_GRAVITY_X, DEATH_GRAVITY_Y);
            m_world->SetGravity(deathGravity);
            m_player->getObject().setOrigin(m_player->getObject().getTextureRect().width/2, m_player->getObject().getTextureRect().height/2);
            break;
        }
        case GameOver: {
            m_player->setAnimate(ResourcesManager::instance().getBarryDeath(1), sf::Vector2u(1, 1), 0.18f);
            b2Vec2 deathGravity(DEATH_GRAVITY_X, DEATH_GRAVITY_Y * 2);
            m_world->SetGravity(deathGravity);
            m_player->getObject().setOrigin(m_player->getObject().getTexture()->getSize().x/2, m_player->getObject().getTexture()->getSize().y/2);
            break;
        }
        default:
            break;
    }
}

void PlayerStateManager::setState(int state) {
    m_state = state;
    switch (m_state) {
        case Regular: {
            m_player->setAnimate(ResourcesManager::instance().getPlayer(), sf::Vector2u(4, 1), 0.18f);
            m_gravityScale = 1.f;
            m_player->getObject().setOrigin(m_player->getObject().getTextureRect().width/2, m_player->getObject().getTextureRect().height/2);
            //b2Vec2 deathGravity(GRAVITATION_X, GRAVITATION_Y);
            //m_world->SetGravity(deathGravity);
            break;
        }
        case SuperPowerTank: {
            m_player->setAnimate(ResourcesManager::instance().getSuperPower(1), sf::Vector2u(2, 1), 0.2f);
            m_player->getObject().setOrigin(m_player->getObject().getTextureRect().width/2, m_player->getObject().getTextureRect().height/2);
            //b2Vec2 deathGravity(GRAVITATION_X, GRAVITATION_Y);
            //m_world->SetGravity(deathGravity);
            m_gravityScale = 1.f; //FIXME
            break;
        }
        case SuperPowerRunner: {
            m_player->setAnimate(ResourcesManager::instance().getSuperPowerRunner(), sf::Vector2u(4, 1), 0.18f);
            m_player->getObject().setRotation(180.f);
            m_player->getObject().setOrigin(m_player->getObject().getTextureRect().width/2, m_player->getObject().getTextureRect().height/2);
            //b2Vec2 deathGravity(- GRAVITATION_X, - GRAVITATION_Y);
            //m_world->SetGravity(deathGravity);
            m_gravityScale = -1.f; //FIXME
            break;
        }
        case DeadPlayer: {
            m_player->setAnimate(ResourcesManager::instance().getBarryDeath(0), sf::Vector2u(4, 1), 0.18f);
            m_player->getObject().setOrigin(m_player->getObject().getTextureRect().width/2, m_player->getObject().getTextureRect().height/2);
            //b2Vec2 deathGravity(DEATH_GRAVITY_X, DEATH_GRAVITY_Y);
            //m_world->SetGravity(deathGravity);
            m_gravityScale = 2.f; //FIXME
            break;
        }
        case GameOver: {
            m_player->setAnimate(ResourcesManager::instance().getBarryDeath(1), sf::Vector2u(1, 1), 0.18f);
            m_player->getObject().setOrigin(m_player->getObject().getTexture()->getSize().x/2, m_player->getObject().getTexture()->getSize().y/2);
            //b2Vec2 deathGravity(DEATH_GRAVITY_X, DEATH_GRAVITY_Y * 2);
            //m_world->SetGravity(deathGravity);
            m_gravityScale = 10.f; //FIXME
            break;
        }
        default:
            break;
    }
    m_player->getBody()->SetGravityScale(m_gravityScale);
}

int PlayerStateManager::getState() const {
    return m_state;
}

sf::Vector2f PlayerStateManager::getPosition() const {
    return m_player->getObject().getPosition();
}

sf::Vector2u PlayerStateManager::getSize() const {
    return m_player->getObject().getTexture()->getSize();
}

bool PlayerStateManager::getIfSuperTank() const {
    return m_wasSuperTank;
}

void PlayerStateManager::setToSuperTank(bool change){
    m_wasSuperTank = change;
}

void PlayerStateManager::setSpacePressed(bool pressed) {
    m_spacePressed = pressed;
    if(!m_spacePressed) {
        m_wasPressed = true;
    } else if (m_spacePressed && m_wasPressed) {
        setSpeed();
        m_wasPressed = false;
    }
}

void PlayerStateManager::setSpeed() {
    if(m_wasPressed){
        m_speed = ANTI_GRAVITY;
    } else if(m_speed >= ANTI_GRAVITY && m_speed <= -2.f){
        m_speed -= 1.f;
    } else {
        m_speed = -2.f;
    }
}

void PlayerStateManager::moveByPress() {
    if (m_spacePressed) {
        float jumpVelocity = ANTI_GRAVITY;
        switch (m_state) {
            case Regular: {
                jumpVelocity = ANTI_GRAVITY * GRAVITATION_Y; //Adjust the jump velocity as needed
                break;
            }
            case SuperPowerTank: {
                jumpVelocity = m_speed * GRAVITATION_Y; //Adjust the jump velocity as needed
                break;
            }
            case SuperPowerRunner: {
                jumpVelocity = -ANTI_GRAVITY * GRAVITATION_Y;
                break;
            }
        }
        m_player->getBody()->SetLinearVelocity(b2Vec2(m_player->getBody()->GetLinearVelocity().x, jumpVelocity));
        b2Vec2 bodyPosition = m_player->getBody()->GetPosition();
        float bodyAngle = m_player->getBody()->GetAngle();
        m_player->getObject().setPosition(bodyPosition.x, bodyPosition.y);
        m_player->getObject().setRotation(bodyAngle * 180.0f / b2_pi);
    }
}

void PlayerStateManager::moveByState() {
    float length = m_player->getObject().getTexture()->getSize().x / 4;
    switch (m_state) {
        case Regular: {
            if(m_spacePressed) {
                m_player->getObject().setTextureRect(sf::IntRect(length * 3, 0, length, m_player->getObject().getTexture()->getSize().y));
            } else if(m_player->getBody()->GetLinearVelocity().y > 0.0f) {
                m_player->getObject().setTextureRect(sf::IntRect(length * 2, 0, length, m_player->getObject().getTexture()->getSize().y));
            } else {
                m_player->animate();
            }
            break;
        }
        case SuperPowerTank: {
            if(m_spacePressed) {
                m_player->setAnimate(ResourcesManager::instance().getSuperPower(2), sf::Vector2u(1, 1), 0.18f);
            } else {
                if(m_player->getBody()->GetLinearVelocity().y > 0.0f) {
                    m_player->setAnimate(ResourcesManager::instance().getSuperPower(1), sf::Vector2u(2, 1), 0.18f);
                    length *= 2;
                    m_player->getObject().setTextureRect(sf::IntRect(length, 0, length, m_player->getObject().getTexture()->getSize().y));
                } else {
                    m_player->animate();
                }
            }
            break;
        }
        case SuperPowerRunner: {
            if (m_spacePressed) {
                m_player->getObject().setTextureRect(sf::IntRect(length * 2, 0, length, m_player->getObject().getTexture()->getSize().y));
            } else if(m_player->getBody()->GetLinearVelocity().y > 0.0f) {
                m_player->getObject().setTextureRect(sf::IntRect(length * 0, 0, length, m_player->getObject().getTexture()->getSize().y));
            } else {
                m_player->animate();
            }
            break;
        }
        case DeadPlayer: {
            m_player->animate();
            break;
        }
        case GameOver: {
            m_player->getBody()->SetLinearVelocity(b2Vec2{0,0});
            m_player->animate();
            break;
        }
        default:
            break;
    }
}

void PlayerStateManager::handleCollisionByState(float collidedType) {
    float elapse = m_playerCollisionTime.getElapsedTime().asSeconds();
    switch (m_state) {
        case Regular: {
            if (elapse >= collidedType || !m_wasSuper) {
                Event event = Event(DeathInTheAir);
                EventsQueue::instance().push(event);
                m_wasSuper = true;
            }
            break;
        }
        case SuperPowerTank: {
            Event event = Event(ReturnRegular);
            EventsQueue::instance().push(event);
            m_playerCollisionTime.restart();
            m_wasSuper = true;
            break;
        }
        case SuperPowerRunner: {
            Event event = Event(ReturnRegular);
            EventsQueue::instance().push(event);
            m_playerCollisionTime.restart();
            m_wasSuper = true;
            break;
        }
        default:
            break;
    }
}