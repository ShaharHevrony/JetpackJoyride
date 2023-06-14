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

void PlayerStateManager::setState(int state) {
    m_state = state;
    switch (m_state) {
        case Regular: {
            m_player->setAnimate(ResourcesManager::instance().getPlayer(), sf::Vector2u(4, 1), 0.18f);
            break;
        }
        case SuperPowerTank: {
            m_player->setAnimate(ResourcesManager::instance().getSuperPower(1), sf::Vector2u(2, 1), 0.2f);
            break;
        }
        case SuperPowerRunner: {
            m_player->setAnimate(ResourcesManager::instance().getSuperPowerRunner(), sf::Vector2u(4, 1), 0.18f);
            break;
        }
        case DeadPlayer: {
            m_player->setAnimate(ResourcesManager::instance().getBarryDeath(0), sf::Vector2u(4, 1), 0.18f);
            break;
        }
        case GameOver: {
            m_player->setAnimate(ResourcesManager::instance().getBarryDeath(1), sf::Vector2u(1, 2), 0.18f);
            break;
        }
    }
}

int PlayerStateManager::getState() const {
    return m_state;
}

void PlayerStateManager::setSpacePressed(bool pressed) {
    m_spacePressed = pressed;
}

bool PlayerStateManager::getSpacePressed() const {
    return m_spacePressed;
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
        default: {
            break;
        }
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
        case DeadPlayer: {
            break;
        }
        case GameOver: {
            break;
        }
        default: {
            break;
        }
    }
}