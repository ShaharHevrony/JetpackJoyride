#pragma once
#include "Box2Object.h"
#include "Player.h"

class Box2Coin: public Box2Object{
public:
    Box2Coin(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC, b2World* world = nullptr, float scale = 0.f, int type = 5);
    virtual ~Box2Coin() = default;

    virtual void create(b2World *world, b2BodyType bodyType);
    virtual void setChange(b2World *world) {}

    virtual void move(float time);
    virtual void draw(sf::RenderWindow* window);
    virtual void updateCollisionTime(float time);

    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player);
    virtual void handleCollision(Obstacle& obstacle) {}
    virtual void handleCollision(Beam& beam) {}
    virtual void handleCollision (Piggy& piggy) {}
    virtual void handleCollision (Box2Coin& box2Coin);
    virtual void handleCollision(Missile& missile) {}
    virtual void handleCollision(SuperPower& SuperPower) {}

};
