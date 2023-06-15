#include "NonCollisionObject.h"

//---------------------------------- NonCollisionObject ---------------------------------
NonCollisionObject::NonCollisionObject(sf::Texture *texture, const sf::Vector2f &position): Object(texture, position) {}

void NonCollisionObject::draw(sf::RenderWindow* window) {
    window->draw(m_object);
}

//---------------------------------------- Flame ----------------------------------------
Flame::Flame(sf::Texture* texture, const sf::Vector2f& position) : NonCollisionObject(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(6, 1), 0.1f);
}

void Flame::move(float time) {
    animate();
    m_object.setPosition(m_playerLoc);
}

void Flame::setPlayerPos(sf::Vector2f pos) {
    m_playerLoc = pos;
}

//---------------------------------------- Lights ---------------------------------------
Lights::Lights(sf::Texture* texture, const sf::Vector2f& position) : NonCollisionObject(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(6, 1), 0.14f);
}

void Lights::move(float time) {
    animate();
    sf::Vector2f direction(-1, 0);
    m_object.move(direction * time);
}

//-------------------------------------- Scientist --------------------------------------
Scientist::Scientist(sf::Texture* texture, const sf::Vector2f& position) : NonCollisionObject(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(3, 1), 0.22f);
}

void Scientist::move(float time) {
    animate();
    sf::Vector2f direction(-1.5, 0);
    m_object.move(direction * time);
}