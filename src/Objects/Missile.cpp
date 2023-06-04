#include "Missile.h"

Missile::Missile() : Object() {}

Missile::Missile(sf::Texture* texture, const sf::Vector2f& position) : Object(texture, position) {}

void Missile::move(float time) {
    animate();
}

void Missile::draw(sf::RenderWindow* window) {
    window->draw(m_object);

}

