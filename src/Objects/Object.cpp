#include "Object.h"
#include "Values.h"

Object::Object(sf::Texture* texture, const sf::Vector2f& position) :m_animation(texture, sf::Vector2u(4, 1), 0.18f) {
    if(texture != nullptr) {
        m_object.setTexture(*texture);
        m_object.setPosition(position);
        m_object.setScale(OBJECT_SCALE, OBJECT_SCALE);
        animate();
    }
}

void Object::move(float time) {
    m_object.move(DIRECTION * time);
}

void Object::setDelete() {
    m_isDelete = true;
}

bool Object::getDelete() const {
    return m_isDelete;
}

void Object::setCollided() {
    m_collided = true;
}

bool Object::getCollided() const{
    return m_collided;
}

void Object::move(float time) {
    m_object.move(DIRECTION * time);
}

void Object::draw(sf::RenderWindow *window) {
    window->draw(m_object);
}

sf::Sprite& Object::getObject() {
    return (sf::Sprite&)m_object;
}

void Object::setAnimate(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {
    m_object.setTexture(*texture);
    m_animation.setAnimation(texture, imageCount, switchTime);
    animate();
}

void Object::animate() {
    m_animation.Update();
    m_object.setTextureRect(m_animation.getObjRec());
}