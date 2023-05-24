#pragma once
#include "Object.h"
class Coins: public Object{
public:
    Coins(sf::Texture* texture, const sf::Vector2f& position);
    ~Coins();
    virtual void move(float time);
};
