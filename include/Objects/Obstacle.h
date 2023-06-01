#pragma once
#include "PairedObject.h"
#include "Coin.h"
//#include "Player.h"

class Obstacle: public PairedObject{
public:
    Obstacle();
    Obstacle(sf::Texture* texture, const sf::Vector2f& position);
    virtual ~Obstacle();

    virtual void space(){}
    virtual void move(float time);
    virtual void draw(sf::RenderWindow* window);
    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player);
    virtual void handleCollision(Obstacle& obstacle);
    virtual void handleCollision(Coin& coin){}
};
