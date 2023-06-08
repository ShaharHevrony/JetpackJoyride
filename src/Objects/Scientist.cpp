#include "Scientist.h"

Scientist::Scientist(sf::Texture* texture, const sf::Vector2f& position) : Object(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(3, 1), 0.22f);
}

void Scientist::move(float time) {
    animate();
    sf::Vector2f direction(-1.5, 0);
    m_object.move(direction * time);
}

void Scientist::draw(sf::RenderWindow* window) {
    window->draw(m_object);
}

//void Scientist::setPlayerPos(sf::Vector2f pos) {
//    m_playerLoc = pos;
//}