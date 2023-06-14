#include "Lights.h"

Lights::Lights(sf::Texture* texture, const sf::Vector2f& position) : Object(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(6, 1), 0.14f);
}

void Lights::move(float time) {
    animate();
    sf::Vector2f direction(-1, 0);
    m_object.move(direction * time);
}

void Lights::draw(sf::RenderWindow* window) {
    window->draw(m_object);
}