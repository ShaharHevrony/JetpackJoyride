#pragma once
#include <box2d/box2d.h>
#include "Object.h"

class Player;
class Coin;
class Laser;

class Box2Object: public Object{
public:
    Box2Object(int type = 0);
    Box2Object(sf::Texture* texture, const sf::Vector2f& position, int type);
    virtual ~Box2Object();
    b2Body* getBody();

    virtual void create(b2World *world, b2BodyType bodyType) = 0;
    virtual void move(float time) = 0;
    virtual void draw(sf::RenderWindow* window) = 0;
    virtual void updateCollisionTime(float time) = 0;

    virtual void handleCollision(Object& object) = 0;
    virtual void handleCollision(Player& player) = 0;
    virtual void handleCollision(Laser& laser) = 0;
    virtual void handleCollision(Beam& beam) = 0;
    virtual void handleCollision (Piggy& piggy) = 0;
    virtual void handleCollision (Coin& coin) = 0;
    virtual void handleCollision(Missile& missile) = 0;
    virtual void handleCollision(SuperPower& SuperPower) = 0;

protected:
    int m_type = 0;
    b2Body* m_body;
};