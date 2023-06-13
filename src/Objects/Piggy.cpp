#include "Piggy.h"

Piggy::Piggy(sf::Texture* texture, const sf::Vector2f& position): Object(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(1, 1), 0.18f);
    m_object.setOrigin(texture->getSize().x/2, texture->getSize().y/2);
}

void Piggy::move(float time) {
    animate();
    sf::Vector2f direction(-1,0);
    m_object.move(direction*time);
}

void Piggy::draw(sf::RenderWindow* window) {
    window->draw(m_object);
}

void Piggy::handleCollision(Object& object) {
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void Piggy::handleCollision(Player& player) {
    player.handleCollision(*this);
}

void Piggy::handleCollision(Piggy& piggy) {}