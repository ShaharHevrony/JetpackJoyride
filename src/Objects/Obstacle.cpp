#include "Obstacle.h"

Obstacle::Obstacle():PairedObject(){}

Obstacle::Obstacle(sf::Texture* texture, const sf::Vector2f &position) :PairedObject(texture, position) {}

Obstacle::~Obstacle() {}

void Obstacle::move(float time) {
    animate();
    sf::Vector2f direction(-1,0);
    if (m_object.getPosition().x < -220.f) {
        m_object.setPosition(WINDOW_WIDTH, m_object.getPosition().y);
    }
    m_object.move(direction*time*65.f);
}

void Obstacle::handleCollision(Object& object) {
    if (&object == this) {
        return;
    } else {
        object.handleCollision(*this);
    }
}

void Obstacle::handleCollision(Obstacle& Obstacle) {}

void Obstacle::handleCollision(Player& player) {
    //player.handleCollision(*this);
}
