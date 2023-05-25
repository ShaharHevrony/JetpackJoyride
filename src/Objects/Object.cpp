#include "Object.h"
#include "Values.h"

Object::Object(sf::Texture* texture, const sf::Vector2f& position, int number): m_animation(texture, sf::Vector2u(4, 1), 0.18f) {
    if(texture != nullptr) {
        m_object.setTexture(*texture);
    }
    m_object.setPosition(position);
    animate(number);
}

Object::~Object() {}

sf::Sprite& Object::getObject() const {
    return (sf::Sprite&)m_object;
}

void Object::setObject(sf::Sprite sprite) {
    m_object = sprite;
}

void Object::animate(int num) {
    std::cout << "##Player number: " << num << "\n";
    m_animation.Update(0);
    m_object.setTextureRect(m_animation.getObjRec());
}