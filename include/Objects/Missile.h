#pragma once
#include "Object.h"

class Missile : public Object {
public:
    Missile();
    Missile(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~Missile() = default;
    virtual void move(float time);

    virtual void handleCollision(Object& object) {}
    virtual void handleCollision(Player& player) {}
    virtual void handleCollision(Obstacle& obstacle) {}
    virtual void handleCollision(Coin& coin) {}
    virtual void draw(sf::RenderWindow* window);
private:

};