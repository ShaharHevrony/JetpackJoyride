#include "Beam.h"

Beam::Beam(sf::Texture* texture, const sf::Vector2f &position, float rotate): Object(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(4, 1), 0.18f);
    m_object.setOrigin(m_object.getTextureRect().width/2, 1.f);
    m_object.setRotation(rotate);
}

void Beam::move(float time) {
    animate();
    sf::Vector2f direction(-1,0);
    m_object.move(direction*time);
}

void Beam::handleCollision(Object& object) {
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void Beam::handleCollision(Player& player) {
    player.handleCollision(*this);
}

void Beam::draw(sf::RenderWindow* window) {
    window->draw(m_object);
}
