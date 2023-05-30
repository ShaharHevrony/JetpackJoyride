#pragma once
#include "Object.h"
#include <cmath>

#define _USE_MATH_DEFINES

class PairedObject: public Object {
public:
    PairedObject();
    PairedObject(sf::Texture* texture, const sf::Vector2f& position);
    virtual ~PairedObject();
    void calculateAngle();
    void setPaired(const sf::Vector2f& position);

    virtual void move(float time) = 0;
    virtual void handleCollision(Object& object) = 0;
    virtual void handleCollision(Player& player) = 0;
    virtual void handleCollision(Obstacle& obstacle) = 0;
    virtual void handleCollision(Coin& coin) = 0;

protected:
    sf::Vector2f m_pairsPosition;
};