#pragma once
#include "Object.h"
#include "Player.h"
#include "Coins.h"


class Obstacle: public Object {
public:
    Obstacle(sf::Texture* texture, const sf::Vector2f &startPosition ,const sf::Vector2f& endPosition, bool second);
    Obstacle(sf::Texture* texture, const sf::Vector2f& position);
    Obstacle();
    ~Obstacle();
    virtual void handleCollision(Object& object) ;

    virtual void handleCollision(Player& player);

    virtual void handleCollision(Obstacle& obstacle);

    virtual void handleCollision(Coins& coins) {}

    virtual void move(float time);
    void calculateAngle(const sf::Vector2f& startPosition, const sf::Vector2f& endPosition, bool second);
private:
    int m_xPos;

};
