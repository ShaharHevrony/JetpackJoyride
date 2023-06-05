#pragma once
#include "Object.h"
#include "FallingCoins.h"
#include "Player.h"

class Piggy :public Object{
public:
    Piggy(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    virtual ~Piggy() = default;
    void createCoins();

    virtual void move(float time);
    virtual void draw(sf::RenderWindow* window);

    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player);
    virtual void handleCollision(Obstacle& obstacle) {}
    virtual void handleCollision(Coin& coin) {}
    virtual void handleCollision(Beam& beam) {}
    virtual void handleCollision (Piggy& piggy) {}

private:
    std::vector<std::unique_ptr<FallingCoins>> m_fallingCoins;
};
