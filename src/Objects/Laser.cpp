#include "Obstacle.h"

Laser::Laser(): PairedObject(){}

Laser::Laser(sf::Texture* texture, const sf::Vector2f &position) : PairedObject(texture, position) {}

void Laser::move(float time) {
    animate();
    sf::Vector2f direction(-1,0);
    m_object.move(direction*time);
}

void Laser::handleCollision(Object& object) {
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void Laser::handleCollision(Player& player) {
    player.handleCollision(*this);
}

void Laser::draw(sf::RenderWindow* window){
    window->draw(m_object);
}
