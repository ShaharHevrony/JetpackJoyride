#include "SuperPower.h"

SuperPower::SuperPower(sf::Texture* texture, const sf::Vector2f& position) : Object(texture, position) {
    // Constructor
    m_animation.setAnimation(texture, sf::Vector2u(1, 1), 0.18f);
}

void SuperPower::move(float time) {
    // Function to move the superpower object
    m_object.move(DIRECTION * time);
}

void SuperPower::handleCollision(Object& object) {
    // Function to handle collision with another object
    // Check if the collided object is not itself and call its handleCollision function
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void SuperPower::handleCollision(Player& player) {
    // Function to handle collision with the player object
    // Call the player's handleCollision function with itself as the parameter
    player.handleCollision(*this);
}
