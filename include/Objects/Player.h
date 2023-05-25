#pragma once
#include "Object.h"
class Player: public Object{
public:
    Player(sf::Texture* texture, const sf::Vector2f& position, int number);
    ~Player();
    virtual void move(float time);
};
