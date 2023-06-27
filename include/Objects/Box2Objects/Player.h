#pragma once
#include "Box2Object.h"
#include "Values.h"
#include "Laser.h"
#include "Beam.h"
#include "Piggy.h"
#include "Coin.h"
#include "Missile.h"
#include "Bound.h"
#include "SuperPower.h"
#include "PlayerStateManager.h"
#include "EventsQueue.h"

class Player: public Box2Object {
public:
    Player(sf::Texture* texture = nullptr, sf::Vector2f position = DEFAULT_VEC, b2World* world = nullptr, int type = 3);
    virtual ~Player() = default;

    virtual void create(b2World *world, b2BodyType bodyType) override;
    virtual void move(float time) override;

    virtual void handleCollision(Object& object) override;
    virtual void handleCollision(Player& player) override;
    virtual void handleCollision(Laser& laser) override;
    virtual void handleCollision(Beam& beam) override;
    virtual void handleCollision (Piggy& piggy) override;
    virtual void handleCollision (Coin& coin) override;
    virtual void handleCollision(Missile& missile) override;
    virtual void handleCollision(SuperPower& SuperPower) override;

private:
    sf::Sound m_CoinCollect;
    sf::Sound m_ZapperSound;
    sf::Sound m_soundHitMissile;
    sf::Sound m_soundGetPowerBox;
};