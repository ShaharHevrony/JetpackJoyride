#pragma once
#include "box2d/box2d.h"
#include "Object.h"

class Player;
class Coin;
class Obstacle;

class Box2dObject: public Object{
public:
    Box2dObject(std::unique_ptr<b2World>* world = nullptr, int type = 0);
    Box2dObject(sf::Texture* texture, const sf::Vector2f& position, std::unique_ptr<b2World>* world, int type);
    virtual ~Box2dObject() = default;
    bool getDeathStat() const;
    b2Body* getBody();
    void setType(int type);
    int getType() const;
    void setSpacePressed(bool pressed);
    bool getSpacePressed() const;

    virtual void create(b2World *world) = 0;
    virtual void setDeath(b2World *world) = 0;

    virtual void move(float time) = 0;
    virtual void draw(sf::RenderWindow* window) = 0;

    virtual void handleCollision(Object& object) = 0;
    virtual void handleCollision(Player& player) = 0;
    virtual void handleCollision(Obstacle& obstacle) = 0;
    virtual void handleCollision(Coin& coin) = 0;
    virtual void handleCollision(Beam& beam) {}

protected:
    int m_type = 0;
    bool m_spacePressed = false;
    b2Body* m_body;
};
