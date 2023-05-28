#include "Obstacle.h"

Obstacle::Obstacle(){}

Obstacle::Obstacle(sf::Texture* texture, const sf::Vector2f &startPosition ,const sf::Vector2f& endPosition, bool second)
        :Object(texture, startPosition) {
    //m_object.setOrigin(texture->getSize().x/2, texture->getSize().y);
    calculateAngle(startPosition, endPosition, second);
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

void Obstacle::handleCollision(Object& object) {
    if (&object == this) {
        return;
    }
    else {
        object.handleCollision(*this);
    }
}

void Obstacle::handleCollision(Obstacle& Obstacle) {}

void Obstacle::handleCollision(Player& player) {
    //player.handleCollision(*this);
}

//void Obstacle::calculateAngle(const sf::Vector2f &startPosition, const sf::Vector2f &endPosition) {
//    // Calculate the delta between the two positions
//    #define M_PI       3.14159265358979323846   // pi
//    sf::Vector2f delta = sf::Vector2f(startPosition.x - endPosition.x, startPosition.y - endPosition.y);
//    float angleRadians = std::atan2(delta.y, delta.x);
//    //Convert the angle from radians to degrees
//    float angleDegrees = angleRadians * (180.0f / M_PI);
//    float lineLength = std::sqrt(delta.x * delta.x + delta.y * delta.y);
//    m_object.setRotation(angleDegrees);
//}
void Obstacle::calculateAngle(const sf::Vector2f& startPosition, const sf::Vector2f& endPosition, bool second) {
    const float PI = 3.14159265358979323846f;
    sf::Vector2f midpoint = (startPosition + endPosition) * 0.5f;
    sf::Vector2f delta = startPosition - midpoint;
    float angleRadians = std::atan2(delta.y, delta.x);
    float angleDegrees = angleRadians * (180.0f / PI);
    angleDegrees += 180.0f;
    angleDegrees = std::fmod(angleDegrees, 360.0f);
    m_object.setRotation(angleDegrees);
    if (startPosition.x == endPosition.x && second == true) {
        sf::Vector2f newPosition = sf::Vector2f(startPosition.x + 300, endPosition.y + 85);
        m_object.setPosition(newPosition);
    }
}




