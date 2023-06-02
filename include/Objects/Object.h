#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "ResourcesManager.h"
#include "Animation.h"
#include "EventsQueue.h"

class Player;
class Obstacle;
class Coin;

class Object {
public:
    Object(sf::Texture* texture = nullptr, const sf::Vector2f& position = sf::Vector2f(0,0));
    Object(Object& other);
    virtual ~Object();
    void animate();
    sf::Sprite getObject();
    void setObject(sf::Texture* texture, sf::Vector2u imageCount);
    bool getCollided() const;
    bool getDelete() const;
    void setCollided();
    void setDelete();
    b2Body* getBody();

    virtual void move(float time) = 0;
    virtual void draw(sf::RenderWindow* window) = 0;
    virtual void handleCollision(Object& object) = 0;
    virtual void handleCollision(Player& player) = 0;
    virtual void handleCollision(Obstacle& obstacle) = 0;
    virtual void handleCollision(Coin& coin) = 0;

protected:
    sf::Sprite m_object;
    Animation m_animation;
    b2Body* m_body;

private:
    bool m_isDelete = false;
    bool m_collided = false;
};
