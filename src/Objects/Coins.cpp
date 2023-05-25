#include "Coins.h"

Coins::Coins(sf::Texture* texture, const sf::Vector2f &position): Object(texture, position) {}

Coins::~Coins() {}

void Coins::move(float time) {
    animate();
    sf::Vector2f direction(-1,0);
    m_object.move(direction*time*65.f);
}