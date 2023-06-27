#include "Piggy.h"

Piggy::Piggy(sf::Texture* texture, const sf::Vector2f& position) : Object(texture, position) {
    // Constructor
    m_animation.setAnimation(texture, sf::Vector2u(1, 1), 0.18f);
    m_object.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
}

void Piggy::move(float time) {
    // Function to move the Piggy object
    m_object.move(DIRECTION * time);
}

void Piggy::handleCollision(Object& object) {
    // Function to handle collision with another object
    // Check if the collided object is not itself and call its handleCollision function
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void Piggy::handleCollision(Player& player) {
    // Function to handle collision with the player object
    // Call the player's handleCollision function with itself as the parameter
    player.handleCollision(*this);
}
