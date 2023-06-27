#include "Laser.h"

Laser::Laser(sf::Texture* texture, const sf::Vector2f& position) : Object(texture, position) {
    // Constructor
    m_object.setOrigin(m_object.getTextureRect().width / DIV_TWO, m_object.getTextureRect().height / DIV_TWO);
    float radius = WINDOW_HEIGHT * ZERO_POINT_ZERO_TWO;
    m_laserShape.setRadius(radius);
    m_laserShape.setPosition(m_object.getPosition());
    m_laserShape.setOrigin(radius, radius);
}

float Laser::calculateAngle(sf::Vector2f otherPosition) {
    // Function to calculate the angle between the laser and another position
    sf::Vector2f midpoint = (m_object.getPosition() + otherPosition) * ZERO_POINT_FIVE;
    sf::Vector2f delta = m_object.getPosition() - midpoint;
    float angleRadians = std::atan2(delta.y, delta.x);
    float angleDegrees = angleRadians * (ONE_EIGHTY / PI) + TWO_SEVENTY;
    angleDegrees = std::fmod(angleDegrees, THREE_SIXTY);
    m_object.setRotation(angleDegrees);
    return angleDegrees;
}

float Laser::calculateDistance(sf::Vector2f otherPosition) {
    // Function to calculate the distance between the laser and another position
    double deltaX = std::abs(m_object.getPosition().x - otherPosition.x);
    double deltaY = std::abs(m_object.getPosition().y - otherPosition.y);
    float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    return distance;
}

sf::CircleShape Laser::getShape() const {
    // Function to get the shape of the laser (circle shape)
    return m_laserShape;
}

void Laser::move(float time) {
    // Function to move the laser
    m_object.move(DIRECTION * time);
    m_laserShape.move(DIRECTION * time);
}

void Laser::handleCollision(Object& object) {
    // Function to handle collision with another object
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void Laser::handleCollision(Player& player) {
    // Function to handle collision with the player
    player.handleCollision(*this);
}
