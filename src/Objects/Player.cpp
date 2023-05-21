#include "Objects/Player.h"

Player::Player(sf::Texture *texture,const sf::Vector2f &position): Object(texture, position){}

Player::~Player() {}

void Player::move(float time, sf::Vector2f position) {
    sf::Vector2f direction(0,0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        direction.y = -1;
    } else {
        direction.y = 1;
    }
    direction.x = 0;
    moveObj(direction, time, position);
}