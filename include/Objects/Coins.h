#pragma once
#include "Object.h"
#include "Obstacle.h"
#include "Player.h"

class Coins: public Object{
public:
    Coins() {};
    Coins(sf::Texture* texture, const sf::Vector2f& position);
    ~Coins();
    virtual void move(float time);

    virtual void handleCollision(Object& object) ;

    virtual void handleCollision(Player& player) ;

    virtual void handleCollision(Obstacle& obstacle) {}

    virtual void handleCollision(Coins& coins);

    bool getSwitchCoins();

private:
    bool m_needSwitchCoins = false;

};
