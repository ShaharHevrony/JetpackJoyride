#include "SuperPower.h"

SuperPower::SuperPower(sf::Texture* texture, const sf::Vector2f& position): Object(texture, position){
    m_animation.setAnimation(texture, sf::Vector2u(1, 1), 0.18f);
}

void SuperPower::move(float time) {
    m_object.move(DIRECTION * time);
}

void SuperPower::handleCollision(Object &object) {
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void SuperPower::handleCollision(Player& player) {
    player.handleCollision(*this);
}