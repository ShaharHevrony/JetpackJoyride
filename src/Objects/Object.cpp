#include "Object.h"
#include "Values.h"

Object::Object(sf::Texture* texture, const sf::Vector2f& position) : m_animation(texture, sf::Vector2u(4, 1), 0.18f) {
    // Constructor
    if (texture != nullptr) {
        m_object.setTexture(*texture);
        m_object.setPosition(position);
        m_object.setScale(OBJECT_SCALE, OBJECT_SCALE);
        animate();
    }
}

void Object::move(float time) {
    // Function to move the object
    m_object.move(DIRECTION * time);
}

void Object::setDelete() {
    // Function to set the object for deletion
    m_isDelete = true;
}

bool Object::getDelete() const {
    // Function to check if the object should be deleted
    return m_isDelete;
}

void Object::setCollided() {
    // Function to set the object as collided
    m_collided = true;
}

bool Object::getCollided() const {
    // Function to check if the object has collided
    return m_collided;
}

void Object::draw(sf::RenderWindow* window) {
    // Function to draw the object on the specified window
    window->draw(m_object);
}

sf::Sprite& Object::getObject() {
    // Function to get the underlying sf::Sprite object
    return (sf::Sprite&)m_object;
}

void Object::setAnimate(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {
    // Function to set the animation for the object
    m_object.setTexture(*texture);
    m_animation.setAnimation(texture, imageCount, switchTime);
    animate();
}

void Object::animate() {
    // Function to animate the object using the animation class
    m_animation.Update();
    m_object.setTextureRect(m_animation.getObjRec());
}
