#pragma once
#include "Object.h"
#include "PlayerStateManager.h"

class Missile : public Object {
public:
    Missile(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC, int missileCount = 0);
    virtual ~Missile() = default;
    virtual void move(float time) override;
    virtual void updateCollisionTime(float time) override;
    virtual void handleCollision(Object& object) override;
    virtual void handleCollision(Player& player) override;

protected:
    int m_missileCount = 0;
    float m_countTime = 0.0f;
    sf::Sound m_soundMissileLaunch;
    sf::Sound m_soundMissileAlarm;
    bool change = false;
};