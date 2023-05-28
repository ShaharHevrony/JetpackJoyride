#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

#include "ResourcesManager.h"
#include "Animation.h"

class Player;
class Obstacle;
class Coins;

class Object {
public:
    Object(sf::Texture* texture, const sf::Vector2f& position);
    Object() {};
    ~Object() {};
    virtual void move(float time) = 0;
    virtual void handleCollision(Object& object) = 0;

    virtual void handleCollision(Player& player) = 0;

    virtual void handleCollision(Obstacle& obstacle) = 0;

    virtual void handleCollision(Coins& coins) = 0;

    bool getCollided() const;

    void setCollided();

    void setDelete();

    bool getDelete() const;


    sf::Sprite& getObject();
    void animate();

protected:
    sf::Sprite m_object;
    Animation m_animation;

private:
    bool m_isDelete = false;

    bool m_collided = false;
};
