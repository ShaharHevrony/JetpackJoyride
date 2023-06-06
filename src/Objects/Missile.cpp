#include "Missile.h"

Missile::Missile(sf::Texture* texture, const sf::Vector2f& position) : Object(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(3, 1), 0.18f);
}

void Missile::move(float time) {
    animate();
}

void Missile::draw(sf::RenderWindow* window) {
    window->draw(m_object);
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

