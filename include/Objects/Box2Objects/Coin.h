#pragma once
#include "Box2Object.h"
#include "Player.h"

class Coin: public Box2Object{
public:
    Coin(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC, b2World* world = nullptr, float scale = 0.f, int type = 5);
    virtual ~Coin() = default;

    virtual void create(b2World *world, b2BodyType bodyType);

    virtual void move(float time) override;
    virtual void draw(sf::RenderWindow* window);
    virtual void updateCollisionTime(float time);

    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player);
    virtual void handleCollision(Laser& laser) {}
    virtual void handleCollision(Beam& beam) {}
    virtual void handleCollision (Piggy& piggy) {}
    virtual void handleCollision (Coin& coin) {}
    virtual void handleCollision(Missile& missile) {}
    virtual void handleCollision(SuperPower& SuperPower) {}

private:
    float m_scale;
};
