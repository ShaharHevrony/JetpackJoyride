#pragma once
#include "Object.h"
class Player: public Object{
public:
    Player(sf::Texture* texture,const sf::Vector2f& position);
    ~Player();
    virtual void move(float time, sf::Vector2f position);
};
