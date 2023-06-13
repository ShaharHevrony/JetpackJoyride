#pragma once
#include <box2d/box2d.h>
#include "Object.h"

class Player;
class Coin;
class Obstacle;

class Box2Object: public Object{
public:
    Box2Object(b2World* world = nullptr, float scale = 0.f, int type = 0);
    Box2Object(sf::Texture* texture, const sf::Vector2f& position, b2World* world, float scale, int type);
    virtual ~Box2Object();
    b2Body* getBody();
    int getType() const;

    virtual void create(b2World *world, b2BodyType bodyType) = 0;
    virtual void setChange(b2World *world) = 0;

    virtual void move(float time) = 0;
    virtual void draw(sf::RenderWindow* window) = 0;
    virtual void updateCollisionTime(float time) = 0;

    virtual void handleCollision(Object& object) = 0;
    virtual void handleCollision(Player& player) = 0;
    virtual void handleCollision(Obstacle& obstacle) = 0;
    virtual void handleCollision(Beam& beam) = 0;
    virtual void handleCollision (Piggy& piggy) = 0;
    virtual void handleCollision (Box2Coin& box2Coin) = 0;
    virtual void handleCollision(Missile& missile) = 0;
    virtual void handleCollision(SuperPower& SuperPower) = 0;

protected:
    int m_type = 0;
    float m_scale = 0.f;
    b2Body* m_body;
};