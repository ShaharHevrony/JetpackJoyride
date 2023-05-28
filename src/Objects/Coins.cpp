#include "Coins.h"

Coins::Coins(sf::Texture* texture, const sf::Vector2f &position): Object(texture, position) {}

Coins::~Coins() {}

void Coins::move(float time) {
    m_needSwitchCoins = false;
    animate();
    sf::Vector2f direction(-1,0);
    if (m_object.getPosition().x < -220.f) {
        m_needSwitchCoins = true;
        m_object.setPosition(WINDOW_WIDTH, m_object.getPosition().y);
    }
    m_object.move(direction*time*65.f);

}

void Coins::handleCollision(Object& object) {
    if (&object == this) {
        return;
    }
    else {
        object.handleCollision(*this);
    }
}

void Coins::handleCollision(Coins& coins) {}

void Coins::handleCollision(Player& player) {
    /*
    if (player.getObject().getGlobalBounds().intersects(getObject().getGlobalBounds())) {
        player->handleCollision(*this, player);

    }*/
    //player.handleCollision(*this);

}


bool Coins::getSwitchCoins() {
    return m_needSwitchCoins;
}