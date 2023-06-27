#pragma once
#include "Object.h"
#include "Coin.h"
#include "Player.h"

class Piggy :public Object {
public:
    Piggy(sf::Texture *texture = nullptr, const sf::Vector2f &position = DEFAULT_VEC);
    virtual ~Piggy() = default;

    virtual void move(float time) override;
    virtual void handleCollision(Object& object) override;
    virtual void handleCollision(Player& player) override;
};