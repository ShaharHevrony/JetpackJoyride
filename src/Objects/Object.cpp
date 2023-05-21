#include "Objects/Object.h"

Object::Object(sf::Texture *texture,const sf::Vector2f& position) {
    if(texture != nullptr){
        m_object.setTexture(*texture);
    }
    m_object.setPosition(position);
}

Object::~Object() {}

void Object::moveObj(sf::Vector2f direction, float time, sf::Vector2f playerPosition) {
    m_object.move(direction*time*120.f);
}

sf::Sprite Object::getObject() const {
    return m_object;
}

void Object::setObject(sf::Sprite sprite) {
    m_object = sprite;
}