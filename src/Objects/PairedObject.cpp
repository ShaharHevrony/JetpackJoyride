#include "PairedObject.h"
#include <math.h>

PairedObject::PairedObject(sf::Texture* texture, const sf::Vector2f& position): Object(texture, position) {
    m_object.setOrigin(m_object.getTextureRect().width/2, m_object.getTextureRect().height/2);
}

PairedObject::~PairedObject() {}

void PairedObject::calculateAngle() {
    sf::Vector2f midpoint = (m_object.getPosition() + m_pairsPosition) * 0.5f;
    sf::Vector2f delta = m_object.getPosition() - midpoint;
    float angleRadians = std::atan2(delta.y, delta.x);
    float angleDegrees = angleRadians * (180.0f / PI) + 270.f;
    angleDegrees = std::fmod(angleDegrees, 360.0f);
    m_object.setRotation(angleDegrees);
}

void PairedObject::setPaired(const sf::Vector2f &position) {
    m_pairsPosition = position;
    calculateAngle();
}

float PairedObject::calculateDistance() {
    double deltaX = std::abs(m_object.getPosition().x - m_pairsPosition.x);
    double deltaY = std::abs(m_object.getPosition().y - m_pairsPosition.y);
    float  distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    return distance;
}