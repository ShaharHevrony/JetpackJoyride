#pragma once
#include "PairedObject.h"
#include "Player.h"

class Obstacle: public PairedObject {
public:
    Obstacle();
    Obstacle(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~Obstacle() = default;

    virtual void move(float time);
    virtual void draw(sf::RenderWindow* window);
    virtual void updateCollisionTime(float time){}

    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player);
    virtual void handleCollision(Obstacle& obstacle);
    virtual void handleCollision(Coin& coin){}
    virtual void handleCollision(Beam& beam){}
    virtual void handleCollision (Piggy& piggy) {}
    virtual void handleCollision (Box2Coin& box2Coin) {}

};
