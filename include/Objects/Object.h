#pragma once
#include <SFML/Graphics.hpp>

#include "ResourcesManager.h"
#include "GameManager.h"
#include "Animation.h"
#include "EventsQueue.h"

class Player;
class Coin;
class Laser;
class Beam;
class Piggy;
class Coin;
class Missile;
class SuperPower;
class Lights;

class Object {
public:
    Object(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    Object(Object& other);
    virtual ~Object() = default;
    void animate();
    sf::Sprite& getObject();
    void setAnimate(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    bool getDelete() const;
    void setDelete();
    void setInUse(bool inUse);
    bool getInUse() const;
    bool getCollided() const;
    virtual void setCollided();

    virtual void move(float time) = 0;
    virtual void draw(sf::RenderWindow* window) = 0;
    virtual void updateCollisionTime(float time) = 0;

    virtual void handleCollision(Object& object) = 0;
    virtual void handleCollision(Player& player) = 0;
    virtual void handleCollision(Laser& laser) = 0;
    virtual void handleCollision(Beam& beam) = 0;
    virtual void handleCollision (Piggy& piggy) = 0;
    virtual void handleCollision (Coin& coin) = 0;
    virtual void handleCollision(Missile& missile) = 0;
    virtual void handleCollision(SuperPower& SuperPower) = 0;

protected:
    sf::Sprite m_object;
    Animation m_animation;
    bool m_inUse = false;
    bool m_isDelete = false;
    float m_collisionTime = 0.f;
    bool m_collided = false;
};
