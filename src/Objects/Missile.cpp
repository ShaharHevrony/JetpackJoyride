#include "Missile.h"

Missile::Missile(sf::Texture* texture, const sf::Vector2f& position) : Object(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(3, 1), 0.18f);
    m_soundMilssileLaunch.setBuffer(ResourcesManager::instance().getSoundMissileLaunch());
    m_soundMissileAlarm.setBuffer(ResourcesManager::instance().getSoundMissileAlarm());

}

void Missile::move(float time) {
    animate();
}

void Missile::draw(sf::RenderWindow* window) {
    window->draw(m_object);
}

void Missile::updateCollisionTime(float time)
{
    if (m_object.getPosition().x == WINDOW_WIDTH) {
        m_soundMissileAlarm.play();
    }
    else if (m_object.getPosition().x == WINDOW_WIDTH - 100) {
        m_soundMilssileLaunch.play();
    }
}

sf::Clock Missile::getTime() {
    return m_missileTimer;
}

void Missile::restartTime() {
    m_missileTimer.restart();
}

float Missile::getCurrPositionX() {
    return m_currPosition;
}

void Missile::setCurrPositionX(float x) {
    m_currPosition = x;
}

