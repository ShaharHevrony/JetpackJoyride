
#include "Setting/AudioManager.h"
#include <cmath>

AudioManager::AudioManager() {}

AudioManager::~AudioManager() {}

void AudioManager::create(int index) {
    sf::Vector2f position = sf::Vector2f(WIDTH_CENTER/6, HEIGHT_CENTER/6);
    m_start = sf::Vector2f(WIDTH_CENTER - 1.5 * position.x, HEIGHT_CENTER - 1.5 * index * position.y);
    m_end   = sf::Vector2f(WIDTH_CENTER + 1.5 * position.x ,HEIGHT_CENTER - 1.5 * index * position.y);

    m_circle.setRadius(SETTING_CIRCLE);
    m_circle.setFillColor(sf::Color(150,150,150));
    m_circle.setOrigin(SETTING_CIRCLE, SETTING_CIRCLE);
    m_circle.setPosition(m_start.x, m_start.y);
    m_type = sf::Text("", ResourcesManager::instance().getFont(), SETTING_SIZE);
    m_type.setPosition(WIDTH_CENTER, m_start.y - position.y);
    m_type.setOrigin(WIDTH_CENTER / 10, (SETTING_CIRCLE - SETTING_SIZE) / 2);
    m_type.setFillColor(sf::Color(150,150,150));
    volumeToPosition();
}

void AudioManager::handleMouseMoved(sf::Vector2f& mouseMove) {
    if (m_grabbed) {
        // Update circle position based on mouse movement
        if (m_circle.getGlobalBounds().contains(mouseMove)) {
            float circleBounds = static_cast<float>(mouseMove.x);
            if (circleBounds < m_start.x) {
                m_circle.setPosition(m_start);
            } else if (circleBounds > m_end.x) {
                m_circle.setPosition(m_end);
            } else {
                m_circle.setPosition(circleBounds, m_start.y);
            }
        }
    }
}

void AudioManager::positionToVolume() {
    sf::Vector2f lineVector = m_end - m_start;
    float lineLength = std::sqrt(lineVector.x * lineVector.x + lineVector.y * lineVector.y);
    sf::Vector2f circleVector = m_circle.getPosition() - m_start;
    float circleDistance = std::sqrt(circleVector.x * circleVector.x + circleVector.y * circleVector.y);
    m_volume = (circleDistance / lineLength) * 100;
}

void AudioManager::volumeToPosition() {
    m_volume = std::max(0, std::min(m_volume, 100));
    float lineLength = std::sqrt(std::pow(m_end.x - m_start.x, 2) + std::pow(m_end.y - m_start.y, 2));
    float distance = (m_volume / 100.f) * lineLength;
    sf::Vector2f lineDirection = m_end - m_start;
    lineDirection /= lineLength;
    sf::Vector2f newPosition = m_start + (lineDirection * distance);
    m_circle.setPosition(newPosition);
}

int AudioManager::getVolume() const{
    return m_volume;
}

void AudioManager::setVolume(int volume) {
    m_volume = volume;
    volumeToPosition();
}

sf::CircleShape AudioManager::getCircle() const {
    return m_circle;
}

sf::Vector2f AudioManager::getStart() const {
    return m_start;
}

sf::Vector2f AudioManager::getEnd() const {
    return m_end;
}

sf::Text AudioManager::getType() const {
    return m_type;
}

void AudioManager::setType(std::string string) {
    positionToVolume();
    m_type.setString(string + std::to_string(m_volume));
}

void AudioManager::setGrabbed(bool grabbed) {
    m_grabbed = grabbed;
}
