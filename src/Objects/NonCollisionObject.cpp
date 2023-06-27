#include "NonCollisionObject.h"

//---------------------------------- NonCollisionObject ---------------------------------
NonCollisionObject::NonCollisionObject(sf::Texture *texture, const sf::Vector2f &position): Object(texture, position), m_firstPosition(position) {}

void NonCollisionObject::setPosition() {
    m_object.setPosition(m_firstPosition);
}

void NonCollisionObject::setInUse(bool inUse) {
    m_inUse = inUse;
}

bool NonCollisionObject::inUse() const {
    return m_inUse;
}

void NonCollisionObject::handleCollision(Object &object) {
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void NonCollisionObject::handleCollision(Player& player) {
    player.handleCollision(*this);
}

//---------------------------------------- Flame ----------------------------------------
Flame::Flame(sf::Texture* texture, const sf::Vector2f& position) :NonCollisionObject(texture, position){
    m_animation.setAnimation(texture, sf::Vector2u(6, 1), 0.1f);
}

void Flame::move(float time) {
    float flamePosX = PlayerStateManager::instance().getPosition().x - PlayerStateManager::instance().getOrigin().x;
    float flamePosY = PlayerStateManager::instance().getPosition().y + PlayerStateManager::instance().getOrigin().y;
    m_object.setPosition(sf::Vector2f(flamePosX, flamePosY));
}

//---------------------------------------- Lights ---------------------------------------
Light::Light(sf::Texture* texture, const sf::Vector2f& position) : NonCollisionObject(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(6, 1), 0.12f);
}

void Light::move(float time) {
    m_object.move(DIRECTION * time);
}

//-------------------------------------- Scientist --------------------------------------
Scientist::Scientist(sf::Texture* texture, const sf::Vector2f& position) : NonCollisionObject(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(3, 1), 0.22f);
}

void Scientist::move(float time) {
    m_object.move(DIRECTION * time * FASTER_SPEED);
}