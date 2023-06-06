#include "Flame.h"

Flame::Flame(sf::Texture* texture, const sf::Vector2f& position) : Object(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(6, 1), 0.18f);
}


void Flame::move(float time) {
    animate();
    m_object.setPosition(m_playerLoc);
}

void Flame::draw(sf::RenderWindow* window) {
    window->draw(m_object);
}

void Flame::setPlayerPos(sf::Vector2f pos) {
    m_playerLoc = pos;
}