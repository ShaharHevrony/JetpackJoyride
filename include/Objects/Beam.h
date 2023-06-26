#pragma once
#include "Object.h"
#include "Player.h"

class Beam : public Object {
public:
    Beam(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC, float rotate = 0.f, float distance = 0.f);
    virtual ~Beam() = default;
    void calculatePoints(float distance);
    std::vector<sf::CircleShape> getCircles() const;

    virtual void move(float time) override;
    virtual void draw(sf::RenderWindow* window);
    virtual void updateCollisionTime(float time){}

    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player);
    virtual void handleCollision(Laser& laser){}
    virtual void handleCollision(Beam& beam){}
    virtual void handleCollision (Piggy& piggy) {}
    virtual void handleCollision (Coin& coin) {}
    virtual void handleCollision(Missile& missile) {}
    virtual void handleCollision(SuperPower& SuperPower){}

private:
    std::vector<sf::CircleShape> m_circles;
};
