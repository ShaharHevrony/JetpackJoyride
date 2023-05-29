#pragma once
#include "Object.h"
#include "Obstacle.h"
#include "Player.h"

class Coin: public Object{
public:
    Coin();
    Coin(sf::Texture* texture, const sf::Vector2f& position);
    ~Coin();

    virtual void move(float time);
    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player);
    virtual void handleCollision(Obstacle& obstacle){}
    virtual void handleCollision(Coin& coin);
    bool getSwitchCoins();
};
