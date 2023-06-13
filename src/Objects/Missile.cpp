#include "Missile.h"

Missile::Missile(sf::Texture* texture, const sf::Vector2f& position) : Object(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(3, 1), 0.18f);
    m_soundMissileLaunch.setBuffer(ResourcesManager::instance().getSoundMissileLaunch());
    m_soundMissileAlarm.setBuffer(ResourcesManager::instance().getSoundMissileAlarm());

}

void Missile::move(float time) {
    animate();
    if (m_countTime >= 5) {
        sf::Vector2f direction(-1, 0);
        m_object.move(direction * time * 1.5f);
    }
}

void Missile::draw(sf::RenderWindow* window) {
    window->draw(m_object);
}

void Missile::updateCollisionTime(float time) {
    if (m_object.getPosition().x == WINDOW_WIDTH + 200) {
        m_soundMissileAlarm.play();
    } else if (m_object.getPosition().x == WINDOW_WIDTH - 100) {
        m_soundMissileLaunch.play();
    }
}

void Missile::changeByTime(float time, sf::Vector2f playerPosition, int index) {
    m_countTime += time;
        if (m_countTime <= 3) {
            m_object.setPosition(WINDOW_WIDTH - 100, playerPosition.y + (index * 90));
            m_currPosition = playerPosition.y + index * 90;
        } else if (m_countTime >= 3 && m_countTime <= 5 && !firstChange) {
            setAnimate(ResourcesManager::instance().getMissile(1), sf::Vector2u(2, 1), 0.18f);
            firstChange = true;
        } else if (m_countTime >= 5 && !secondChange){
            setAnimate(ResourcesManager::instance().getMissile(2), sf::Vector2u(7, 1), 0.1f);
            secondChange = true;
        }
    updateCollisionTime(time);
}