#pragma once
#include <cmath>
#include "Object.h"

class Player;
class Obstacle;

class PairedObject: public Object {
public:
    PairedObject(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~PairedObject() = default;
    float calculateAngle();
    float calculateDistance();
    void setPaired(const sf::Vector2f& position);

    virtual void move(float time) = 0;
    virtual void draw(sf::RenderWindow* window) = 0;
    virtual void updateCollisionTime(float time){}

    virtual void handleCollision(Object& object) = 0;
    virtual void handleCollision(Player& player) = 0;
    virtual void handleCollision(Obstacle& obstacle) = 0;
    virtual void handleCollision(Beam& beam) = 0;
    virtual void handleCollision (Piggy& piggy) = 0;
    virtual void handleCollision (Box2Coin& box2Coin) = 0;
    virtual void handleCollision(Missile& missile) = 0;
    virtual void handleCollision(SuperPower& SuperPower) = 0;

protected:
    sf::Vector2f m_pairPosition;
};
