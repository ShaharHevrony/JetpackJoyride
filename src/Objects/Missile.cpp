#include "Missile.h"

Missile::Missile(sf::Texture* texture, const sf::Vector2f& position, int missileCount) : Object(texture, position), m_missileCount(missileCount) {
    // Constructor
    m_animation.setAnimation(texture, sf::Vector2u(3, 1), 0.18f);
    m_soundMissileLaunch.setBuffer(ResourcesManager::instance().getSoundMissileLaunch());
    m_soundMissileAlarm.setBuffer(ResourcesManager::instance().getSoundMissileAlarm());
    m_soundMissileLaunch.setVolume(GameManager::instance().getSound());
    m_soundMissileAlarm.setVolume(GameManager::instance().getSound());

    m_object.setOrigin(m_object.getTextureRect().width / 2, m_object.getTextureRect().height / 2);
}

void Missile::move(float time) {
    // Function to move the missile
    if (m_countTime >= 5.f) {
        m_object.move(DIRECTION * time * 1.5f);
    }
}

void Missile::updateCollisionTime(float time) {
    // Function to update the collision time and handle animations and sounds
    m_countTime += time;
    if (m_countTime <= 3.f) {
        m_object.setPosition(WINDOW_WIDTH - 100, PlayerStateManager::instance().getPosition().y + m_missileCount * m_object.getTextureRect().height * OBJECT_SCALE);
    }
    else if (m_countTime >= 3.f && m_countTime <= 5.f && !change) {
        setAnimate(ResourcesManager::instance().getMissile(1), sf::Vector2u(2, 1), 0.18f);
        change = true;
    }
    else if (m_countTime >= 5.f && change) {
        setAnimate(ResourcesManager::instance().getMissile(2), sf::Vector2u(7, 1), 0.1f);
        change = false;
    }
    if (m_object.getPosition().x == WINDOW_WIDTH + 200) {
        m_soundMissileAlarm.play();
    }
    else if (m_object.getPosition().x == WINDOW_WIDTH - 100) {
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
