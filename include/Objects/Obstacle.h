#pragma once
#include "Object.h"

class Obstacle: public Object {
public:
    Obstacle(sf::Texture* texture, const sf::Vector2f &startPosition ,const sf::Vector2f& endPosition);
    Obstacle(sf::Texture* texture, const sf::Vector2f& position);
    Obstacle();
    ~Obstacle();
    virtual void move(float time);
    void calculateAngle(const sf::Vector2f &startPosition ,const sf::Vector2f& endPosition);
};
