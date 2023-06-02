#pragma once
#include <box2d/box2d.h>

#include "Object.h"
#include "Coin.h"
#include "Obstacle.h"

class Player: public Object {
public:
    Player(sf::Texture* texture, sf::Vector2f position, std::unique_ptr<b2World>* world);
    virtual ~Player() = default;
    void create(b2World *world);
    void setDeath(b2World *world);
    void playAnimationOnce(sf::Texture* tempTex);
    void moveRightDown();
    void setSpace(bool space);
    bool getSpace() const;
    bool getDeathStat() const;

    virtual void move(float time);
    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player) {}
    virtual void handleCollision(Obstacle& obstacle);
    virtual void handleCollision(Coin& coin);
    virtual void draw(sf::RenderWindow* window);

private:
    bool m_space = false;
    bool m_death = false;
};
