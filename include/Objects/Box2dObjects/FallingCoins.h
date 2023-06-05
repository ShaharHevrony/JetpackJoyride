#pragma once
#include "Box2dObject.h"
class FallingCoins: public Box2dObject{
public:
    FallingCoins(sf::Texture* texture = nullptr, sf::Vector2f position = DEFAULT_VEC, std::unique_ptr<b2World>* world = nullptr, int type = 2) {}
    virtual ~FallingCoins() = default;

    virtual void create(b2World *world) {}
    virtual void setDeath(b2World* world) {}

    virtual void move(float time) {}
    virtual void draw(sf::RenderWindow* window) {}

    virtual void handleCollision(Object& object) {}
    virtual void handleCollision(Player& player) {}
    virtual void handleCollision(Obstacle& obstacle) {}
    virtual void handleCollision(Coin& coin) {}
    virtual void handleCollision(Beam& beam) {}
    virtual void handleCollision (Piggy& piggy) {}
};
