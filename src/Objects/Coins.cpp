#include "Coin.h"

Coin::Coin(): Object() {}

Coin::Coin(sf::Texture* texture, const sf::Vector2f &position): Object(texture, position) {}

Coin::~Coin() {}

void Coin::move(float time) {
    animate();
    sf::Vector2f direction(-1,0);
    m_object.move(direction*time);
}

void Coin::handleCollision(Object& object) {
    if (&object == this) {
        return;
    }
    else {
        object.handleCollision(*this);
    }
}

void Coin::handleCollision(Coin& coin) {}

void Coin::handleCollision(Player& player) {
//    player.handleCollision(*this);
}

void Coin::draw(sf::RenderWindow* window){
    window->draw(m_object);
}