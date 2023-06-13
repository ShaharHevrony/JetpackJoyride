#pragma once
#include "Object.h"

class Missile : public Object {
public:
    Missile(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~Missile() = default;
    void changeByTime(float time, sf::Vector2f playerPosition, int index);

    virtual void move(float time);
    virtual void draw(sf::RenderWindow* window);
    virtual void updateCollisionTime(float time);

    virtual void handleCollision(Object& object) {}
    virtual void handleCollision(Player& player) {}
    virtual void handleCollision(Obstacle& obstacle) {}
    virtual void handleCollision(Beam& beam) {}
    virtual void handleCollision (Piggy& piggy) {}
    virtual void handleCollision (Box2Coin& box2Coin) {}
    virtual void handleCollision(Missile& missile) {}
    virtual void handleCollision(SuperPower& SuperPower) {}


protected:
    float m_countTime = 0.0f;
    float m_currPosition;
    sf::Sound m_soundMissileLaunch;
    sf::Sound m_soundMissileAlarm;
    bool firstChange = false;
    bool secondChange = false;
};