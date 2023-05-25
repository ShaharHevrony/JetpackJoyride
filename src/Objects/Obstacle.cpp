#include "Obstacle.h"

Obstacle::Obstacle(){}

Obstacle::Obstacle(sf::Texture* texture, const sf::Vector2f &startPosition ,const sf::Vector2f& endPosition)
        :Object(texture, startPosition) {
    //m_object.setOrigin(texture->getSize().x/2, texture->getSize().y);
    calculateAngle(startPosition, endPosition);
}

Obstacle::Obstacle(sf::Texture* texture, const sf::Vector2f &position): Object(texture, position) {
}

Obstacle::~Obstacle() {}

void Obstacle::move(float time) {
    animate();
    sf::Vector2f direction(-1,0);
    if (m_object.getPosition().x < -220.f) {
        m_object.setPosition(WINDOW_WIDTH, m_object.getPosition().y);
    }
    m_object.move(direction*time*65.f);
}

void Obstacle::calculateAngle(const sf::Vector2f &startPosition, const sf::Vector2f &endPosition) {
    // Calculate the delta between the two positions
    sf::Vector2f delta = sf::Vector2f(startPosition.x - endPosition.x, startPosition.y - endPosition.y);
    float angleRadians = std::atan2(delta.y, delta.x);
    //Convert the angle from radians to degrees
    float angleDegrees = angleRadians * (180.0f / M_PI);
    float lineLength = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    m_object.setRotation(angleDegrees);
}
