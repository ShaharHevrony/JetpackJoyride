#pragma once
#include "box2d/box2d.h"
#include "Object.h"

class Floor : public Object{
public:
    Floor(std::unique_ptr<b2World>* world);
    void create(b2World* world);

    virtual void space(){}
    virtual void move(float time) {}
    virtual void handleCollision(Object& object) {}
    virtual void handleCollision(Player& player) {}
    virtual void handleCollision(Obstacle& obstacle) {}
    virtual void handleCollision(Coin& coin){}
    virtual void draw(sf::RenderWindow* window);
};

class Ceiling : public Object{
public:
    Ceiling(std::unique_ptr<b2World>* world);
    void create(b2World* world);

    virtual void space(){}
    virtual void move(float time) {}
    virtual void handleCollision(Object& object) {}
    virtual void handleCollision(Player& player) {}
    virtual void handleCollision(Obstacle& obstacle) {}
    virtual void handleCollision(Coin& coin){}
    virtual void draw(sf::RenderWindow* window);
};

