#pragma once

#include "Object.h"


class Flame : public Object {

public:
    Flame();
    Flame(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~Flame() = default;
    virtual void move(float time);
    void setPlayerPos(sf::Vector2f pos);
    void draw(sf::RenderWindow* window);
    void setFlying(bool);
    bool getFlying();

    virtual void handleCollision(Object& object) {}
    virtual void handleCollision(Player& player) {}
    virtual void handleCollision(Obstacle& obstacle){}
    virtual void handleCollision(Coin& coin) {}
    virtual void handleCollision(Beam& beam){}
    virtual void handleCollision (Piggy& piggy) {}

private:
    sf::Vector2f m_playerLoc;

    bool m_flying = false;
};