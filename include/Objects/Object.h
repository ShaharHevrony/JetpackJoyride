#pragma once
#include <SFML/Graphics.hpp>
#include "ResourcesManager.h"
#include "Animation.h"

class Player;

class Object {
public:
    Object(sf::Texture* texture, const sf::Vector2f& position, int number);
    ~Object();
    virtual void move(float time) = 0;
    sf::Sprite& getObject() const;
    void setObject(sf::Sprite sprite);
    void animate(int number);

protected:
    sf::Sprite m_object;
    Animation m_animation;
};
