#include "Missile.h"

Missile::Missile(sf::Texture* texture, const sf::Vector2f& position, int missileCount)
    :Object(texture, position), m_missileCount(missileCount) {
    m_animation.setAnimation(texture, sf::Vector2u(3, 1), 0.18f);
    m_soundMissileLaunch.setBuffer(ResourcesManager::instance().getSoundMissileLaunch());
    m_soundMissileAlarm.setBuffer(ResourcesManager::instance().getSoundMissileAlarm());
    m_soundMissileLaunch.setVolume(GameManager::instance().getSound());
    m_soundMissileAlarm.setVolume(GameManager::instance().getSound());

    m_object.setOrigin(m_object.getTextureRect().width/2, m_object.getTextureRect().height/2);
}

void Missile::move(float time) {
    if (m_countTime >= 5) {
        m_object.move(DIRECTION * time * FASTER_SPEED);
    } else if (m_object.getPosition().x >= WINDOW_WIDTH + 200) {
        m_object.move(DIRECTION * time * FASTER_SPEED);
    }
}

void Missile::draw(sf::RenderWindow* window) {
    window->draw(m_object);
}

void Missile::updateCollisionTime(float time) {
    m_countTime += time;
    sf::Vector2f position = sf::Vector2f(WINDOW_WIDTH - 100, PlayerStateManager::instance().getPosition().y  + PlayerStateManager::instance().getOrigin().y + m_missileCount*100);
    if (m_countTime <= 3) {
        m_object.setPosition(position);
        m_positionY = position.y;
    } else if (m_countTime >= 3 && m_countTime <= 5 && !m_firstChange) {
        setAnimate(ResourcesManager::instance().getMissile(1), sf::Vector2u(2, 1), 0.18f);
        m_firstChange = true;
    } else if (m_countTime >= 5 && !m_secondChange) {
        setAnimate(ResourcesManager::instance().getMissile(2), sf::Vector2u(7, 1), 0.1f);
        m_secondChange = true;
    }
    if (m_object.getPosition().x == WINDOW_WIDTH + 200) {
        m_soundMissileAlarm.play();
    } else if (m_object.getPosition().x == WINDOW_WIDTH - 100) {
        m_soundMissileLaunch.play();
    }
}