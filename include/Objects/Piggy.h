#pragma once
#include "Object.h"
#include "Coin.h"
#include "Player.h"

class Piggy :public Object {
public:
    Piggy(sf::Texture *texture = nullptr, const sf::Vector2f &position = DEFAULT_VEC);
    virtual ~Piggy() = default;

    virtual void draw(sf::RenderWindow *window);
    virtual void updateCollisionTime(float time) {}

    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player);
    virtual void handleCollision(Laser& laser) {}
    virtual void handleCollision(Beam& beam) {}
    virtual void handleCollision(Piggy& piggy);
    virtual void handleCollision(Coin& coin) {}
    virtual void handleCollision(Missile& missile) {}
    virtual void handleCollision(SuperPower& SuperPower) {}

};