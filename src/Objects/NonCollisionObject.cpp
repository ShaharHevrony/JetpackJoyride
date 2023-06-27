#include "NonCollisionObject.h"

//---------------------------------- NonCollisionObject ---------------------------------
//Constructor
NonCollisionObject::NonCollisionObject(sf::Texture* texture, const sf::Vector2f& position) : Object(texture, position), m_firstPosition(position) {}

//Function to set the position of the non-collision object
void NonCollisionObject::setPosition() {
    m_object.setPosition(m_firstPosition);
}

//Function to set the in-use state of the non-collision object
void NonCollisionObject::setInUse(bool inUse) {
    m_inUse = inUse;
}

//Function to check if the non-collision object is in use
bool NonCollisionObject::inUse() const {
    return m_inUse;
}

//Function to handle collision with another object
void NonCollisionObject::handleCollision(Object& object) {
    if (&object != this) {
        object.handleCollision(*this);
    }
}

//Function to handle collision with the player
void NonCollisionObject::handleCollision(Player& player) {
    player.handleCollision(*this);
}

//---------------------------------------- Flame ----------------------------------------
Flame::Flame(sf::Texture* texture, const sf::Vector2f& position) : NonCollisionObject(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(SIX, FIRST), ZERO_POINT_ONE);
}

//Function to move the flame
void Flame::move(float time) {
    float flamePosX = PlayerStateManager::instance().getPosition().x - PlayerStateManager::instance().getOrigin().x / SECOND;
    float flamePosY = PlayerStateManager::instance().getPosition().y;
    m_object.setPosition(sf::Vector2f(flamePosX, flamePosY));
}


//---------------------------------------- Lights ---------------------------------------
Light::Light(sf::Texture* texture, const sf::Vector2f& position) : NonCollisionObject(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(SIX, FIRST), ZERO_POINT_ONE_TWO);
}

//Function to move the light
void Light::move(float time) {
    m_object.move(DIRECTION * time);
}

//-------------------------------------- Scientist --------------------------------------
Scientist::Scientist(sf::Texture* texture, const sf::Vector2f& position) : NonCollisionObject(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(THIRD, FIRST), ZERO_POINT_TWO_TWO);
}

//Function to move the scientist
void Scientist::move(float time) {
    m_object.move(DIRECTION * time * FASTER_SPEED);
}
