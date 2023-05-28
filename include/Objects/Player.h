#pragma once
#include "Object.h"
#include "Coins.h"
#include "Obstacle.h"

class Player: public Object{
public:
    Player(sf::Texture* texture, const sf::Vector2f& position);
    Player() {};
    ~Player();
    virtual void move(float time);
    virtual void handleCollision(Object& object);

    virtual void handleCollision(Player& player) ;

    virtual void handleCollision(Obstacle& obstacle) ;

    virtual void handleCollision(Coins& coins) ;
};
