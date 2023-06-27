#pragma once
#include <box2d/box2d.h>
#include "Object.h"

class Player;
class Coin;
class Laser;
class Bound;

class Box2Object: public Object {
public:
    Box2Object(int type = 0);
    Box2Object(sf::Texture* texture, const sf::Vector2f& position, int type);
    virtual ~Box2Object();
    b2Body* getBody();

    virtual void create(b2World *world, b2BodyType bodyType) = 0;
    virtual void draw(sf::RenderWindow* window) override;

    virtual void handleCollision(Object& object) override = 0;
    virtual void handleCollision(Player& player) override = 0;
    virtual void handleCollision(Laser& laser) override{}
    virtual void handleCollision(Beam& beam) override{}
    virtual void handleCollision (Piggy& piggy) override{}
    virtual void handleCollision (Coin& coin) override{}
    virtual void handleCollision(Missile& missile) override{}
    virtual void handleCollision(SuperPower& SuperPower) override{}

protected:
    int m_type = 0;
    b2Body* m_body;
};