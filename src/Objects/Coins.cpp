#include "Coin.h"

Coin::Coin(sf::Texture* texture, const sf::Vector2f &position): Object(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(4, 1), 0.18f);
}

void Coin::move(float time) {
    animate();
    sf::Vector2f direction(-1,0);
    m_object.move(direction*time);
}

void Coin::draw(sf::RenderWindow* window){
    window->draw(m_object);
}

void Coin::handleCollision(Object& object) {
    if (&object == this) {
        return;
    }
    else {
        object.handleCollision(*this);
    }
}

void Coin::handleCollision(Player& player) {
    player.handleCollision(*this);
}

void Coin::handleCollision(Coin& coin) {}

void Coin::updateCollisionTime(float time) {
    if (m_collided) {
        m_collisionTime += time;
    }
    if (m_collisionTime >= 0.3f) {
        m_isDelete = true;
    }
}