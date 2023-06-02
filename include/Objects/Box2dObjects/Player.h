#pragma once
#include "box2d/box2d.h"

#include "Box2dObject.h"
#include "Coin.h"
#include "Obstacle.h"

class Player: public Box2dObject {
public:
    Player(sf::Texture* texture = nullptr, sf::Vector2f position = DEFAULT_VEC, std::unique_ptr<b2World>* world = nullptr, int type = 2);
    virtual ~Player() = default;

    virtual void create(b2World *world);
    virtual void setDeath(b2World* world);

    virtual void move(float time);
    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player) {}
    virtual void handleCollision(Obstacle& obstacle);
    virtual void handleCollision(Coin& coin);
    virtual void draw(sf::RenderWindow* window);
};
