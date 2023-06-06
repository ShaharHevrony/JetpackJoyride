#pragma once
#include "Box2Object.h"

class Bound: public Box2Object{
public:
    Bound(b2World* world = nullptr, float scale = 0.f, int type = 0);
    virtual ~Bound() = default;

    virtual void create(b2World *world);
    virtual void setChange(b2World* world);
    virtual void move(float time) {}
    virtual void draw(sf::RenderWindow* window);
    virtual void updateCollisionTime(float time) {}

    virtual void handleCollision(Object& object) {}
    virtual void handleCollision(Player& player) {}
    virtual void handleCollision(Obstacle& obstacle) {}
    virtual void handleCollision(Coin& coin) {}
    virtual void handleCollision(Beam& beam) {}
    virtual void handleCollision (Piggy& piggy) {}
    virtual void handleCollision (Box2Coin& box2Coin) {}

};
