#pragma once
#include <math.h>

#include "Object.h"
#include "Player.h"

class Laser: public Object {
public:
    Laser(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~Laser() = default;
    float calculateAngle(sf::Vector2f otherPosition);
    float calculateDistance(sf::Vector2f otherPosition);
    sf::CircleShape getShape() const;

    virtual void move(float time) override;
    virtual void handleCollision(Object& object) override;
    virtual void handleCollision(Player& player) override;

private:
    sf::CircleShape m_laserShape;
};
