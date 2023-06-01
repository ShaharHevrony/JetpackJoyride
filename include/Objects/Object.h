#pragma once
#include <SFML/Graphics.hpp>
#include "ResourcesManager.h"
#include "PlayGame/Animation.h"
#include "Events/EventsQueue.h"
#include "box2d/box2d.h"

class Player;
class Obstacle;
class Coin;

class Object {
public:
    Object(sf::Texture* texture = nullptr, const sf::Vector2f& position = sf::Vector2f(0,0));
    Object(Object& other);
    virtual ~Object();
    void animate();
    sf::Sprite& getObject();
    void setSprite(sf::Sprite& obj);
    void draw(sf::RenderWindow* window);
    bool getCollided() const;
    bool getDelete() const;
    void setCollided();
    void setDelete();

    virtual void space() = 0;
    virtual void move(float time) = 0;
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
