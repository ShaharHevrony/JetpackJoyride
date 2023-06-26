#pragma once
#include "Object.h"
#include "PlayerStateManager.h"

class Missile : public Object {
public:
    Missile(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC, int missileCount = 0);
    virtual ~Missile() = default;

    virtual void move(float time) override;
    virtual void draw(sf::RenderWindow* window);
    virtual void updateCollisionTime(float time);

    virtual void handleCollision(Object& object) {}
    virtual void handleCollision(Player& player) {}
    virtual void handleCollision(Laser& laser) {}
    virtual void handleCollision(Beam& beam) {}
    virtual void handleCollision (Piggy& piggy) {}
    virtual void handleCollision (Coin& coin) {}
    virtual void handleCollision(Missile& missile) {}
    virtual void handleCollision(SuperPower& SuperPower) {}


protected:
    int m_missileCount = 0;
    float m_countTime = 0.0f;
    float m_positionY;
    sf::Sound m_soundMissileLaunch;
    sf::Sound m_soundMissileAlarm;
    bool m_firstChange = false;
    bool m_secondChange = false;
};