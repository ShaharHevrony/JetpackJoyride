#pragma once
#include "PairedObject.h"
#include "Coin.h"
#include "Player.h"

class Obstacle: public PairedObject{
public:
    Obstacle();
    Obstacle(sf::Texture* texture, const sf::Vector2f& position);
    ~Obstacle();

    virtual void move(float time);
    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player);
    virtual void handleCollision(Obstacle& obstacle);
    virtual void handleCollision(Coin& coin) {}
};
