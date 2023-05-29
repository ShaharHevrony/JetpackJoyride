#include "PairedObject.h"

PairedObject::PairedObject() : Object() {}

PairedObject::PairedObject(sf::Texture* texture, const sf::Vector2f& position)
        : Object(texture, position) {
    m_object.setOrigin(m_object.getTextureRect().width/2, m_object.getTextureRect().height/2);
}

PairedObject::~PairedObject() {}

void PairedObject::calculateAngle() {
    sf::Vector2f midpoint = (m_object.getPosition() + m_pairsPosition) * 0.5f;
    sf::Vector2f delta = m_object.getPosition() - midpoint;
    float angleRadians = std::atan2(delta.y, delta.x);
    float angleDegrees = angleRadians * (180.0f );
    angleDegrees += 270.0f;
    angleDegrees = std::fmod(angleDegrees, 360.0f);
    m_object.setRotation(angleDegrees);
    if (m_object.getPosition().x == m_pairsPosition.x) {
        sf::Vector2f newPosition = sf::Vector2f(m_object.getPosition().x + 300, m_pairsPosition.y + 85);
        m_object.setPosition(newPosition);
    }
}

void PairedObject::setPaired(const sf::Vector2f &position) {
    m_pairsPosition = position;
    calculateAngle();
}
