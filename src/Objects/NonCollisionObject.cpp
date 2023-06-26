#include "NonCollisionObject.h"

//---------------------------------- NonCollisionObject ---------------------------------
NonCollisionObject::NonCollisionObject(sf::Texture *texture, const sf::Vector2f &position): Object(texture, position){}

void NonCollisionObject::draw(sf::RenderWindow* window) {
    window->draw(m_object);
}

//---------------------------------------- Flame ----------------------------------------
Flame::Flame(sf::Texture* texture, const sf::Vector2f& position) : NonCollisionObject(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(6, 1), 0.1f);
    m_type = Flames;
}

void Flame::move(float time) {
    float flamePosX = PlayerStateManager::instance().getPosition().x - PlayerStateManager::instance().getOrigin().x;
    float flamePosY = PlayerStateManager::instance().getPosition().y + PlayerStateManager::instance().getOrigin().y;
    m_object.setPosition(sf::Vector2f(flamePosX, flamePosY));
}

//---------------------------------------- Lights ---------------------------------------
Light::Light(sf::Texture* texture, const sf::Vector2f& position) : NonCollisionObject(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(6, 1), 0.1f);
    m_type = Lights;
}

//-------------------------------------- Scientist --------------------------------------
Scientist::Scientist(sf::Texture* texture, const sf::Vector2f& position) : NonCollisionObject(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(3, 1), 0.2f);
    m_type = Scientists;
}

void Scientist::move(float time) {
    m_object.move(DIRECTION * time * FASTER_SPEED);
}