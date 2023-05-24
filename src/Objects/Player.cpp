#include "Player.h"
#include <iostream>

Player::Player(sf::Texture* texture, const sf::Vector2f &position) :Object(texture, position) {}

Player::~Player() {}

void Player::move(float time) {
    sf::Vector2f direction(0,0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        direction.y = -1;
        direction.x = 0;
    } else {
        direction.y = 1;
        direction.x = 0;
    }

    if(m_object.getPosition().y < 800 && m_object.getPosition().y > 50) {
        if(direction.y == -1){
            m_object.setTextureRect(sf::IntRect(124.75*3,0,124.75,171));
        } else {
            m_object.setTextureRect(sf::IntRect(124.75*2,0,124.75,171));
        }
        m_object.move(direction*time*SPEED);
    } else if(m_object.getPosition().y >= 800 && direction.y == -1) {
        m_object.setTextureRect(sf::IntRect(124.75*3,0,124.75,171));
        m_object.move(direction*time*SPEED);
    } else if(m_object.getPosition().y <= 50 && direction.y == 1) {
        m_object.setTextureRect(sf::IntRect(124.75*2,0,124.75,171));
        m_object.move(direction*time*SPEED);
    } else {
        if(m_object.getPosition().y >= 800) {
            animate();
        } else {
            m_object.setTextureRect(sf::IntRect(124.75*3,0,124.75,171));
        }
    }
}
