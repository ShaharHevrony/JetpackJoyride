#pragma once
#include "box2d/box2d.h"
#include "Object.h"

class Floor : public Object{
public:
    Floor(std::unique_ptr<b2World>* world);
    void createSquareBody(b2World* world, b2BodyType bodyType, sf::Vector2i rect = { 0, 0 });

    virtual void space(){}
    virtual void move(float time) {}
    virtual void handleCollision(Object& object) {}
    virtual void handleCollision(Player& player) {}
    virtual void handleCollision(Obstacle& obstacle) {}
    virtual void handleCollision(Coin& coin){}
};


