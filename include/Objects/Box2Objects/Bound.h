#pragma once
#include "Box2Object.h"
#include "Player.h"

class Bound: public Box2Object{
public:
    Bound(b2World* world = nullptr, int type = 0);
    virtual ~Bound() = default;

    virtual void create(b2World *world, b2BodyType bodyType) override;
    virtual void move(float time) override {}

    virtual void handleCollision(Object& object) override;
    virtual void handleCollision(Player& player) override;
};
