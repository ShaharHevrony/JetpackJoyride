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

void PlayerStateManager::setPlayer(Player& player) {
    m_player = std::make_shared<Player>(player);
    m_state  = Regular;
}

void PlayerStateManager::setState(int state) {
    m_state = state;
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
            } else {
                m_player->getObject().setTextureRect(sf::IntRect(length * 2, 0, length, m_player->getObject().getTexture()->getSize().y));
            }
            break;
        }
        case SuperPowerTank: {
            if(m_spacePressed) {
                m_player->setAnimate(ResourcesManager::instance().getSuperPower(2), sf::Vector2u(1, 1), 0.18f);
            } else {
                m_player->setAnimate(ResourcesManager::instance().getSuperPower(1), sf::Vector2u(2, 1), 0.18f);
                length *= 2;
                m_player->getObject().setTextureRect(sf::IntRect(length, 0, length, m_player->getObject().getTexture()->getSize().y));
            }
            break;
        }
        case SuperPowerRunner: {
            if (m_spacePressed) {
                m_player->setAnimate(ResourcesManager::instance().getSuperPowerRunner(), sf::Vector2u(1, 1), 0.18f);
            }
            else {
                m_player->setAnimate(ResourcesManager::instance().getSuperPowerRunner(), sf::Vector2u(2, 1), 0.18f);
                length = length * 2;
                m_player->getObject().setTextureRect(sf::IntRect(length, 0, length, m_player->getObject().getTexture()->getSize().y));
            }
            break;
        }
        case DeadPlayer: {
            break;
        }
        case GameOver: {
            m_player->getBody()->SetLinearVelocity(b2Vec2{0,0});
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