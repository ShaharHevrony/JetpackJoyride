#include "AudioManager.h"
#include <cmath>

AudioManager::AudioManager() {}

AudioManager::~AudioManager() {}

void AudioManager::create(int index) {
    sf::Vector2f position = sf::Vector2f(WIDTH_CENTER / 6, HEIGHT_CENTER / 6);

    //Calculate start and end positions based on the index
    if (index == SECOND) {
        m_start = sf::Vector2f(WIDTH_CENTER - 3.5f * position.x, HEIGHT_CENTER + index * position.y);
        m_end = sf::Vector2f(WIDTH_CENTER - position.x, HEIGHT_CENTER + index * position.y);
    } else if (index == 1) {
        m_start = sf::Vector2f(WIDTH_CENTER - 3.5f * position.x, HEIGHT_CENTER + index / 15.0f * position.y);
        m_end = sf::Vector2f(WIDTH_CENTER - position.x, HEIGHT_CENTER + index / 15.0f * position.y);
    }

    //Set properties of the circle:
    m_circle.setRadius(SETTING_CIRCLE);
    m_circle.setFillColor(sf::Color::White);
    m_circle.setOutlineColor(sf::Color::Black);
    m_circle.setOutlineThickness(5.f);
    m_circle.setOrigin(SETTING_CIRCLE, SETTING_CIRCLE);
    m_circle.setPosition(m_start.x, m_start.y);

    //Set properties of the type text:
    m_type = sf::Text("", ResourcesManager::instance().getFont(), SETTING_SIZE);
    m_type.setPosition(WIDTH_CENTER, m_start.y - position.y);
    m_type.setOrigin(WIDTH_CENTER / TEN, (SETTING_CIRCLE - SETTING_SIZE) / SECOND);
    m_type.setFillColor(sf::Color::White);
    m_type.setOutlineColor(sf::Color::Black);
    m_type.setOutlineThickness(FIVE_F);
    volumeToPosition(); //Adjust the circle position based on the volume value
}

void AudioManager::handleMouseMoved(sf::Vector2f& mouseMove) {
    if (m_grabbed) {
        //Update circle position based on mouse movement
        if (m_circle.getGlobalBounds().contains(mouseMove)) {
            float circleBounds = static_cast<float>(mouseMove.x);
            if (circleBounds < m_start.x) {
                m_circle.setPosition(m_start);
            }
            else if (circleBounds > m_end.x) {
                m_circle.setPosition(m_end);
            }
            else {
                m_circle.setPosition(circleBounds, m_start.y);
            }
        }
    }
}
float AudioManager::positionToVolume() {
    //Calculate the line vector and length
    sf::Vector2f lineVector = m_end - m_start;
    float lineLength = std::sqrt(lineVector.x * lineVector.x + lineVector.y * lineVector.y);
    //Calculate the circle vector and distance from the start
    sf::Vector2f circleVector = m_circle.getPosition() - m_start;
    float circleDistance = std::sqrt(circleVector.x * circleVector.x + circleVector.y * circleVector.y);
    //Calculate the volume based on the circle's distance from the start and the line length
    m_volume = (circleDistance / lineLength) * HUNDRED;
    return m_volume;
}

void AudioManager::volumeToPosition() {
    //Clamp the volume value between 0 and 100
    m_volume = std::max(ZERO, std::min(m_volume, HUNDRED));

    //Calculate the line length and the distance based on the volume
    float lineLength = std::sqrt(std::pow(m_end.x - m_start.x, SECOND) + std::pow(m_end.y - m_start.y, SECOND));
    float distance = (m_volume / 100.f) * lineLength;

    //Calculate the new position along the line based on the distance
    sf::Vector2f lineDirection = m_end - m_start;
    lineDirection /= lineLength;
    sf::Vector2f newPosition = m_start + (lineDirection * distance);
    m_circle.setPosition(newPosition); //Set the new position of the circle
}

//Set the volume value and update the circle position accordingly
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

void AudioManager::setGrabbed(bool grabbed) {
    m_grabbed = grabbed;
}