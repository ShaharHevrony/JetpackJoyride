#pragma once
#include <SFML/Graphics.hpp>
#include "ResourcesManager.h"
#include "Animation.h"
#include "EventsQueue.h"

class Player;
class Obstacle;
class Coin;

class Object {
public:
    Object();
    Object(sf::Texture* texture, const sf::Vector2f& position);
    Object(Object& other);
    virtual ~Object();
    void animate();
    sf::Sprite& getObject();
    void setSprite(sf::Sprite& obj);

    bool getCollided() const;
    bool getDelete() const;
    void setCollided();
    void setDelete();
    virtual void move(float time) = 0;
    virtual void handleCollision(Object& object) = 0;
    virtual void handleCollision(Player& player) = 0;
    virtual void handleCollision(Obstacle& obstacle) = 0;
    virtual void handleCollision(Coin& coin) = 0;

protected:
    sf::Sprite m_object;
    Animation m_animation;
    //const sf::Vector2f& m_position;


private:
    bool m_isDelete = false;
    bool m_collided = false;
};
