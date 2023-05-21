#pragma once
#include <SFML/Graphics.hpp>
class Object {
public:
    Object(sf::Texture* texture,const sf::Vector2f& position);
    ~Object();
    virtual void move(float time, sf::Vector2f position) = 0;
    void moveObj(sf::Vector2f direction, float time, sf::Vector2f playerPosition);
    sf::Sprite getObject() const;
    void setObject(sf::Sprite sprite);

protected:
    sf::Sprite m_object;
};
