#pragma once
#include "Object.h"

class Missile : public Object {
public:
    Missile(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~Missile() = default;
    sf::Clock getTime();
    void restartTime();
    float getCurrPositionX();
    void setCurrPositionX(float x);

    virtual void move(float time);
    virtual void draw(sf::RenderWindow* window);
    virtual void updateCollisionTime(float time){}

    virtual void handleCollision(Object& object) {}
    virtual void handleCollision(Player& player) {}
    virtual void handleCollision(Obstacle& obstacle) {}
    virtual void handleCollision(Coin& coin) {}
    virtual void handleCollision(Beam& beam) {}
    virtual void handleCollision (Piggy& piggy) {}
    virtual void handleCollision (Box2Coin& box2Coin) {}

protected:
    sf::Clock m_missileTimer;   // Timer for tracking the time
    float m_currPosition;
};