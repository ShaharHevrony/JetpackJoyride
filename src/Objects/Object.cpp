#include "Object.h"
#include "Values.h"

Object::Object(sf::Texture* texture, const sf::Vector2f& position) :m_animation(texture, sf::Vector2u(4, 1), 0.18f) {
    if(texture != nullptr) {
        m_object.setTexture(*texture);
    }
    m_object.setPosition(position);
    m_object.setScale(SET_OBJ_SCALE, SET_OBJ_SCALE);
    animate();
}

Object::Object(Object& other) {
    m_object.setTexture(*other.getObject().getTexture());
    m_object.setPosition(other.getObject().getPosition());
    m_object.setRotation(other.getObject().getRotation());
}

void Object::setDelete() {
    m_isDelete = !m_isDelete;
}

bool Object::getDelete() const {
    return m_isDelete;
}

void Object::setInUse(bool inUse) {
    m_inUse = inUse;
}

bool Object::getInUse() const{
    return m_inUse;
}

void Object::setCollided() {
    m_collided = !m_collided;
}

bool Object::getCollided() const{
    return m_collided;
}

sf::Sprite& Object::getObject() {
    return (sf::Sprite&)m_object;
}

void Object::setObject(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {
    m_object.setTexture(*texture);
    m_animation.setAnimation(texture, imageCount, switchTime);
    animate();
}

void Object::animate() {
    m_animation.Update();
    m_object.setTextureRect(m_animation.getObjRec());
}

Animation Object::getAnimation() const {
    return m_animation;
}