#include "Laser.h"

Laser::Laser(sf::Texture* texture, const sf::Vector2f& position) : Object(texture, position) {
    // Constructor
    m_object.setOrigin(m_object.getTextureRect().width / 2, m_object.getTextureRect().height / 2);
    float radius = WINDOW_HEIGHT * 0.02;
    m_laserShape.setRadius(radius);
    m_laserShape.setPosition(m_object.getPosition());
    m_laserShape.setOrigin(radius, radius);
}

float Laser::calculateAngle(sf::Vector2f otherPosition) {
    // Function to calculate the angle between the laser and another position
    sf::Vector2f midpoint = (m_object.getPosition() + otherPosition) * 0.5f;
    sf::Vector2f delta = m_object.getPosition() - midpoint;
    float angleRadians = std::atan2(delta.y, delta.x);
    float angleDegrees = angleRadians * (180.0f / PI) + 270.f;
    angleDegrees = std::fmod(angleDegrees, 360.0f);
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
