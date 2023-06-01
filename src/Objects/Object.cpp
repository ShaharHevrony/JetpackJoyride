#include "Object.h"
#include "Values.h"

Object::Object(sf::Texture* texture, const sf::Vector2f& position) :m_animation(texture, sf::Vector2u(4, 1), 0.18f){
    if(texture != nullptr) {
        m_object.setTexture(*texture);
    }
    m_object.setPosition(position);
    m_object.setScale(SET_SCALE, SET_SCALE);
    animate();
}

Object::Object(Object& other) {
    m_object.setTexture(*other.getObject().getTexture());
    m_object.setPosition(other.getObject().getPosition());
    m_object.setRotation(other.getObject().getRotation());
}

Object::~Object() {}

bool Object::getCollided() const {
    return m_collided;
}

void Object::setCollided() {
    m_collided = !m_collided;
}

void Object::setDelete() {
    m_isDelete = !m_isDelete;
}

bool Object::getDelete() const {
    return m_isDelete;
}

sf::Sprite& Object::getObject() {
    return (sf::Sprite&)m_object;
}

void Object::setSprite(sf::Sprite& obj) {
    m_object = obj;
}

void Object::animate() {
    m_animation.Update();
    m_object.setTextureRect(m_animation.getObjRec());
}

b2Body* Object::getBody() {
    return m_body;
}
