#pragma once
#include "Box2Object.h"
#include "Values.h"
#include "Obstacle.h"
#include "Beam.h"
#include "Piggy.h"
#include "Box2Coin.h"
#include "Missile.h"
#include "SuperPower.h"
#include "PlayerStateManager.h"

class Player: public Box2Object {
public:
    Player(sf::Texture* texture = nullptr, sf::Vector2f position = DEFAULT_VEC, b2World* world = nullptr, int type = 3);
    virtual ~Player() = default;

    virtual void create(b2World *world, b2BodyType bodyType);
    virtual void setChange(b2World *world);
    virtual void move(float time);
    virtual void draw(sf::RenderWindow* window);
    virtual void updateCollisionTime(float time) {}

    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player);
    virtual void handleCollision(Obstacle& obstacle);
    virtual void handleCollision(Beam& beam);
    virtual void handleCollision (Piggy& piggy);
    virtual void handleCollision (Box2Coin& box2Coin);
    virtual void handleCollision(Missile& missile);
    virtual void handleCollision(SuperPower& SuperPower);

private:
    sf::Sound m_CoinCollect;
    sf::Sound m_ZapperSound;
    sf::Sound m_soundHitMissile;
};