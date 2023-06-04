#pragma once
#include <SFML/Graphics.hpp>

#include "ResourcesManager.h"
#include "Animation.h"
#include "EventsQueue.h"

class Player;
class Coin;
class Obstacle;
class Beam;

class Object {
public:
    Object(sf::Texture* texture = nullptr, const sf::Vector2f& position = DEFAULT_VEC);
    Object(Object& other);
    virtual ~Object() = default;
    void animate();
    Animation getAnimation() const;
    sf::Sprite& getObject();
    void setObject(sf::Texture* texture, sf::Vector2u imageCount);
    bool getCollided() const;
    bool getDelete() const;
    void setCollided();
    void setDelete();

    virtual void move(float time) = 0;
    virtual void draw(sf::RenderWindow* window) = 0;

    virtual void handleCollision(Object& object) = 0;
    virtual void handleCollision(Player& player) = 0;
    virtual void handleCollision(Obstacle& obstacle) = 0;
    virtual void handleCollision(Coin& coin) = 0;
    virtual void handleCollision(Beam& beam) = 0;

protected:
    sf::Sprite m_object;
    Animation m_animation;

private:
    bool m_isDelete = false;
    bool m_collided = false;
};
