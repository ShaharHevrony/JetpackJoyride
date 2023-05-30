#pragma once
#include "Object.h"
#include "Coin.h"
#include "Obstacle.h"

class ScoreBoard;

class Player: public Object{
public:
    Player();
    Player(sf::Texture* texture, const sf::Vector2f& position);
    virtual ~Player();

    virtual void move(float time);
    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player);
    virtual void handleCollision(Obstacle& obstacle);
    virtual void handleCollision(Coin& coin);
};
