#pragma once
#include <math.h>

#include "Object.h"
#include "Player.h"

class Laser: public Object {
public:
    Laser(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~Laser() = default;
    float calculateAngle(sf::Vector2f otherPosition);
    float calculateDistance(sf::Vector2f otherPosition);

    virtual void draw(sf::RenderWindow* window);
    virtual void updateCollisionTime(float time){}

    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player);
    virtual void handleCollision(Laser& laser) {}
    virtual void handleCollision(Beam& beam){}
    virtual void handleCollision (Piggy& piggy) {}
    virtual void handleCollision (Coin& coin) {}
    virtual void handleCollision(Missile& missile) {}
    virtual void handleCollision(SuperPower& SuperPower) {}
};
