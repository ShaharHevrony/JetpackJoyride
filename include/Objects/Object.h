#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

#include "ResourcesManager.h"
#include "Animation.h"

class Player;

class Object {
public:
    Object(sf::Texture* texture, const sf::Vector2f& position);
    Object() {};
    ~Object();
    virtual void move(float time) = 0;
    sf::Sprite& getObject() const;
    void animate();

protected:
    sf::Sprite m_object;
    Animation m_animation;
};
