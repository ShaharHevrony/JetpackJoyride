#pragma once
#include "Object.h"
#include "PlayerStateManager.h"

//---------------------------------- NonCollisionObject ---------------------------------
class NonCollisionObject : public Object {
public:
    NonCollisionObject(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~NonCollisionObject() = default;
    void setInUse(bool inUse);
    bool inUse() const;
    void setPosition();

    virtual void move(float time) override = 0;
    virtual void handleCollision(Object& object) override;
    virtual void handleCollision(Player& player) override;

private:
    sf::Vector2f m_firstPosition;
    bool m_inUse = false;
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
    virtual void move(float time) override;
};

//-------------------------------------- Scientist --------------------------------------
class Scientist : public NonCollisionObject {
public:
    Scientist(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~Scientist() = default;
    virtual void move(float time) override;
};