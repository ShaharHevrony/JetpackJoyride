#pragma once
#include "Player.h"

class Player;
class Obstacle;

class Coin: public Object{
public:
    Coin();
    Coin(sf::Texture* texture, const sf::Vector2f& position);
    virtual ~Coin();
    bool getSwitchCoins();

    virtual void move(float time);
    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player);
    virtual void handleCollision(Obstacle& obstacle){}
    virtual void handleCollision(Coin& coin);
    virtual void draw(sf::RenderWindow* window);
};
