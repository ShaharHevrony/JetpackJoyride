#include "SuperPower.h"

void SuperPower::move(float time) {
    animate();
    sf::Vector2f direction(-1, 0);
    m_object.move(direction * time);
}

void SuperPower::draw(sf::RenderWindow* window) {
    window->draw(m_object);
}

void SuperPower::handleCollision(Object& object)
{
    if (&object == this) {
        return;
    }
    else {
        object.handleCollision(*this);
    }
}

void SuperPower::handleCollision(Player& player)
{
    player.handleCollision(*this);

}

