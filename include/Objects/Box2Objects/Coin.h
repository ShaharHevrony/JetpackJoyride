#pragma once
#include "Box2Object.h"
#include "Player.h"

class Coin: public Box2Object{
public:
    Coin(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC, b2World* world = nullptr, float scale = 0.f, int type = 5);
    virtual ~Coin() = default;

    virtual void create(b2World *world, b2BodyType bodyType) override;
    virtual void move(float time) override;
    virtual void updateCollisionTime(float time) override;

    virtual void handleCollision(Object& object) override;
    virtual void handleCollision(Player& player) override;

private:
    float m_scale;
};
