#include "SuperPower.h"

SuperPower::SuperPower(sf::Texture* texture, const sf::Vector2f& position): Object(texture, position){
    m_animation.setAnimation(texture, sf::Vector2u(1, 1), 0.18f);
}

void SuperPower::move(float time) {
    animate();
    sf::Vector2f direction(-1, 0);
    m_object.move(direction * time);
}

void SuperPower::draw(sf::RenderWindow* window) {
    window->draw(m_object);
}

void SuperPower::handleCollision(Object& object) {
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void SuperPower::handleCollision(Player& player) {
    player.handleCollision(*this);
}