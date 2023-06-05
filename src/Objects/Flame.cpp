#include "Flame.h"


Flame::Flame() : Object() {}

Flame::Flame(sf::Texture* texture, const sf::Vector2f& position) : Object(texture, position) {}


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

void Flame::setFlying(bool flying) {
    m_flying = flying;
}

bool Flame::getFlying() {
    return m_flying;
}
