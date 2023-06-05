
#include "Piggy.h"

Piggy::Piggy(sf::Texture* texture, const sf::Vector2f& position): Object(texture, position) {
    m_fallingCoins.clear();
}

void Piggy::createCoins() {
    for(int index = 0; index < 100; index++) {
        //m_fallingCoins.push_back(std::make_unique<FallingCoins>());
    }
}

void Piggy::move(float time) {
    animate();
    sf::Vector2f direction(-1,0);
    m_object.move(direction*time);
    for (auto &coins: m_fallingCoins) {
        //coins->move(TIME_STEP);
    }
}

void Piggy::draw(sf::RenderWindow* window) {
    window->draw(m_object);
    for (auto &coins: m_fallingCoins) {
        //coins->draw(window);
    }
}

void Piggy::handleCollision(Object& object) {
    if (&object == this) {
        return;
    }
    else {
        object.handleCollision(*this);
    }
}

void Piggy::handleCollision(Player& player) {
    player.handleCollision(*this);
}