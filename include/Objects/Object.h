#pragma once
#include <SFML/Graphics.hpp>
#include "ResourcesManager.h"
#include "Animation.h"

class PlayGame;

class Object {
public:
    Object(sf::Texture* texture,const sf::Vector2f& position);
    ~Object();
    virtual void move(float time) = 0;
    sf::Sprite& getObject() const;
    void setObject(sf::Sprite sprite);

    static sf::Clock playerTime;

protected:
    sf::Sprite m_object;
    Animation m_animation;
};
