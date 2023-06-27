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
    virtual void handleCollision(Object& object) override;
    virtual void handleCollision(Player& player) override;

private:
    std::vector<sf::CircleShape> m_circles;
};
