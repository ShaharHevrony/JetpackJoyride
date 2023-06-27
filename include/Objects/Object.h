#pragma once
#include <SFML/Graphics.hpp>

#include "ResourcesManager.h"
#include "GameManager.h"
#include "Animation.h"
//#include "EventsQueue.h"

class Player;
class Coin;
class Laser;
class Beam;
class Piggy;
class Coin;
class Missile;
class SuperPower;
class Light;
class Bound;

class Object {
public:
    Object(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~Object() = default;
    void animate();
    sf::Sprite& getObject();
    void setAnimate(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    bool getDelete() const;
    void setDelete();
    bool getCollided() const;

    virtual void setCollided();
    virtual void move(float time);
    virtual void draw(sf::RenderWindow* window);
    virtual void updateCollisionTime(float time){}

    virtual void handleCollision(Object& object) = 0;
    virtual void handleCollision(Player& player) = 0;
    virtual void handleCollision(Laser& laser){}
    virtual void handleCollision(Beam& beam){}
    virtual void handleCollision (Piggy& piggy){}
    virtual void handleCollision (Coin& coin){}
    virtual void handleCollision(Missile& missile){}
    virtual void handleCollision(SuperPower& SuperPower){}

protected:
    sf::Sprite m_object;
    Animation m_animation;
    bool m_isDelete = false;
    float m_collisionTime = 0.f;
    bool m_collided = false;
};
