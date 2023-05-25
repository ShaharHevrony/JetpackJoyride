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

    if(m_object.getPosition().y < 650 && m_object.getPosition().y > 70) {
        if(direction.y == -1){
            m_object.setTextureRect(sf::IntRect(110*3,0,110,150));
        } else {
            m_object.setTextureRect(sf::IntRect(110*2,0,110,150));
        }
        m_object.move(direction*time*SPEED);
    } else if(m_object.getPosition().y >= 650 && direction.y == -1) {
        m_object.setTextureRect(sf::IntRect(110*3,0,110,150));
        m_object.move(direction*time*SPEED);
    } else if(m_object.getPosition().y <= 70 && direction.y == 1) {
        m_object.setTextureRect(sf::IntRect(110*2,0,110,150));
        m_object.move(direction*time*SPEED);
    } else {
        if(m_object.getPosition().y >= 650) {
            animate();
        } else {
            m_object.setTextureRect(sf::IntRect(110*3,0,110,150));
        }
    }
}

//void Player::move(float time) {}