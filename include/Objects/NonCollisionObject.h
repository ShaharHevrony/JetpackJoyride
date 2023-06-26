#pragma once
#include "Object.h"
#include "PlayerStateManager.h"

//---------------------------------- NonCollisionObject ---------------------------------
class NonCollisionObject : public Object {
public:
    NonCollisionObject(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~NonCollisionObject() = default;

    virtual void draw(sf::RenderWindow* window);
    virtual void updateCollisionTime(float time) {}

    virtual void handleCollision(Object& object) {}
    virtual void handleCollision(Player& player) {}
    virtual void handleCollision(Laser& laser){}
    virtual void handleCollision(Beam& beam){}
    virtual void handleCollision (Piggy& piggy) {}
    virtual void handleCollision (Coin& coin) {}
    virtual void handleCollision(Missile& missile) {}
    virtual void handleCollision(SuperPower& SuperPower) {}

protected:
    int m_type = 0;
};

//---------------------------------------- Flame ----------------------------------------
class Flame : public NonCollisionObject {
public:
    Flame(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~Flame() = default;
    virtual void move(float time) override;
};

//---------------------------------------- Lights ---------------------------------------
class Light : public NonCollisionObject {
public:
    Light(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~Light() = default;
};

//-------------------------------------- Scientist --------------------------------------
class Scientist : public NonCollisionObject {
public:
    Scientist(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~Scientist() = default;
    virtual void move(float time) override;
};