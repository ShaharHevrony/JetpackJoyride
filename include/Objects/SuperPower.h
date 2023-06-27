#pragma once
#include "Player.h"

class SuperPower: public Object {
public:
    SuperPower(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~SuperPower() = default;

    virtual void move(float time) override;
    virtual void handleCollision(Object& object) override;
    virtual void handleCollision(Player& player) override;
};