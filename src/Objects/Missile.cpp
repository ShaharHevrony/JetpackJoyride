#include "Missile.h"

Missile::Missile(sf::Texture* texture, const sf::Vector2f& position, int missileCount) : Object(texture, position), m_missileCount(missileCount) {
    // Constructor
    m_animation.setAnimation(texture, sf::Vector2u(THIRD, FIRST), ZERO_POINT__ONE_EIGHT);
    m_soundMissileLaunch.setBuffer(ResourcesManager::instance().getSoundMissileLaunch());
    m_soundMissileAlarm.setBuffer(ResourcesManager::instance().getSoundMissileAlarm());
    m_soundMissileLaunch.setVolume(GameManager::instance().getSound());
    m_soundMissileAlarm.setVolume(GameManager::instance().getSound());

    m_object.setOrigin(m_object.getTextureRect().width / DIV_TWO, m_object.getTextureRect().height / DIV_TWO);
}

void Missile::move(float time) {
    // Function to move the missile
    if (m_countTime >= FIVE_F) {
        m_object.move(DIRECTION * time * ONE_POINT_FIVE);
    }
}

void Missile::updateCollisionTime(float time) {
    // Function to update the collision time and handle animations and sounds
    m_countTime += time;
    if (m_countTime <= THREE_F) {
        m_object.setPosition(WINDOW_WIDTH - HUNDRED, PlayerStateManager::instance().getPosition().y + m_missileCount * m_object.getTextureRect().height * OBJECT_SCALE);
    }
    else if (m_countTime >= THREE_F && m_countTime <= FIVE_F && !change) {
        setAnimate(ResourcesManager::instance().getMissile(FIRST), sf::Vector2u(SECOND, FIRST), ZERO_POINT__ONE_EIGHT);
        change = true;
    }
    else if (m_countTime >= FIVE_F && change) {
        setAnimate(ResourcesManager::instance().getMissile(SECOND), sf::Vector2u(SEVEN, FIRST), ZERO_POINT_ONE);
        change = false;
    }
    if (m_object.getPosition().x == WINDOW_WIDTH + TWO_HUNDRED) {
        m_soundMissileAlarm.play();
    }
    else if (m_object.getPosition().x == WINDOW_WIDTH - HUNDRED) {
        m_soundMissileLaunch.play();
    }
}

void Missile::handleCollision(Object& object) {
    // Function to handle collision with another object
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void Missile::handleCollision(Player& player) {
    // Function to handle collision with the player
    player.handleCollision(*this);
}
