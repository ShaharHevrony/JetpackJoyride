#include "PairedObject.h"
#include <math.h>

PairedObject::PairedObject(sf::Texture* texture, const sf::Vector2f& position): Object(texture, position) {
    m_object.setOrigin(m_object.getTextureRect().width/2, m_object.getTextureRect().height/2);
}

float PairedObject::calculateAngle(sf::Vector2f otherPosition) {
    sf::Vector2f midpoint = (m_object.getPosition() + otherPosition) * 0.5f;
    sf::Vector2f delta = m_object.getPosition() - midpoint;
    float angleRadians = std::atan2(delta.y, delta.x);
    float angleDegrees = angleRadians * (180.0f / PI) + 270.f;
    angleDegrees = std::fmod(angleDegrees, 360.0f);
    m_object.setRotation(angleDegrees);
    return angleDegrees;
}

float PairedObject::calculateDistance(sf::Vector2f otherPosition) {
    double deltaX = std::abs(m_object.getPosition().x - otherPosition.x);
    double deltaY = std::abs(m_object.getPosition().y - otherPosition.y);
    float  distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    return distance;
}