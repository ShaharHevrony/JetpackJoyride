#pragma once
#include <Box2D/Box2D.h>

#include "Object.h"

class TempPlayer :public Object{
public:
    TempPlayer(sf::Texture* texture, sf::Vector2f position, std::unique_ptr<b2World>* world);
    virtual ~TempPlayer() = default;
    void create(b2World *world,b2BodyType bodyType, float radius);
    void createSensor(b2World* world, float width, float height, b2Vec2 center, int data);
    void move(bool isJumping);

    virtual void move(float time) {
    }
    virtual void handleCollision(Object& object) {}
    virtual void handleCollision(Player& player) {}
    virtual void handleCollision(Obstacle& obstacle) {}
    virtual void handleCollision(Coin& coin) {}

private:
};
