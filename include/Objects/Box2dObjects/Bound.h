#pragma once
#include <box2d/box2d.h>
#include "Box2dObject.h"

class Bound: public Box2dObject{
public:
    Bound(std::unique_ptr<b2World>* world = nullptr, int type = 0);
    virtual ~Bound() = default;

    virtual void create(b2World *world);
    virtual void setDeath(b2World* world);

    virtual void move(float time) {}
    virtual void draw(sf::RenderWindow* window);

    virtual void handleCollision(Object& object) {}
    virtual void handleCollision(Player& player) {}
    virtual void handleCollision(Obstacle& obstacle) {}
    virtual void handleCollision(Coin& coin) {}
    virtual void handleCollision(Beam& beam) {}

};

