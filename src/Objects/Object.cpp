#include "Object.h"
#include "Values.h"

Object::Object(sf::Texture* texture, const sf::Vector2f& position): m_animation(texture, sf::Vector2u(4, 1), 0.18f) {
    if(texture != nullptr) {
        m_object.setTexture(*texture);
    }
    m_object.setPosition(position);
    //m_object.setOrigin(texture->getSize().x, texture->getSize().y);
    animate();
}

Object::~Object() {}

sf::Sprite& Object::getObject() const {
    return (sf::Sprite&)m_object;
}

void Object::animate() {
    m_animation.Update();
    m_object.setTextureRect(m_animation.getObjRec());
}