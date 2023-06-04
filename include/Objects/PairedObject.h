#pragma once
#include <cmath>
#include "Object.h"

class Player;
class Coin;
class Obstacle;

class PairedObject: public Object {
public:
    PairedObject(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~PairedObject() = default;
    float calculateAngle();
    float calculateDistance();
    void setPaired(const sf::Vector2f& position);

    virtual void move(float time) = 0;
    virtual void draw(sf::RenderWindow* window) = 0;

    virtual void handleCollision(Object& object) = 0;
    virtual void handleCollision(Player& player) = 0;
    virtual void handleCollision(Obstacle& obstacle) = 0;
    virtual void handleCollision(Coin& coin) = 0;
    virtual void handleCollision(Beam& beam) = 0;

protected:
    sf::Vector2f m_pairPosition;
};
