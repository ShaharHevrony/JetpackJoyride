#include "Beam.h"

Beam::Beam(sf::Texture* texture, const sf::Vector2f& position, float rotate, float distance) : Object(texture, position) {
    // Constructor
    m_animation.setAnimation(texture, sf::Vector2u(BUTTON_NUM_DIV_TWO, FIRST), ZERO_POINT__ONE_EIGHT);
    m_object.setOrigin(m_object.getTextureRect().width / SECOND, ONE_POINT_ZERO);
    m_object.setRotation(rotate);
    calculatePoints(distance);
}

void Beam::calculatePoints(float distance) {
    // Function to calculate the points along the beam
    float size = std::min(ResourcesManager::instance().getPlayerStates(GameManager::instance().getCharacter(), Regular)->getSize().x,
        ResourcesManager::instance().getPlayerStates(GameManager::instance().getCharacter(), Regular)->getSize().y) * ZERO_POINT_EIGHT / PLAYER_SCALE;
    int numOfCircle = (distance / size) + FIRST;
    float radius = WINDOW_HEIGHT * ZERO_POINT_ZERO_TWO;
    float angleRadians = (m_object.getRotation() + NINETY) * (PI / ONE_EIGHTY);
    sf::Vector2f currentPosition = m_object.getPosition();

    for (int count = 0; count < numOfCircle; count++) {
        sf::CircleShape tempCircle(radius);
        tempCircle.setPosition(currentPosition);
        tempCircle.setOrigin(radius, radius);
        m_circles.push_back(tempCircle);

        float deltaX = (distance / numOfCircle) * std::cos(angleRadians);
        float deltaY = (distance / numOfCircle) * std::sin(angleRadians);
        currentPosition += sf::Vector2f(deltaX, deltaY);
    }
}

std::vector<sf::CircleShape> Beam::getCircles() const {
    //Function to get the vector of circles representing the points along the beam
    return m_circles;
}

void Beam::move(float time) {
    //Function to move the beam and its points
    m_object.move(DIRECTION * time);
    for (auto& point : m_circles) {
        point.move(DIRECTION * time);
    }
}

void Beam::handleCollision(Object& object) {
    // Function to handle collision with another object
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void Beam::handleCollision(Player& player) {
    // Function to handle collision with the player
    player.handleCollision(*this);
}
