#include "Beam.h"

Beam::Beam(sf::Texture* texture, const sf::Vector2f &position, float rotate, float distance): Object(texture, position) {
    m_animation.setAnimation(texture, sf::Vector2u(4, 1), 0.18f);
    m_object.setOrigin(m_object.getTextureRect().width/2, 1.f);
    m_object.setRotation(rotate);
    calculatePoints(distance);
}

void Beam::calculatePoints(float distance) {
    float size = std::min(ResourcesManager::instance().getPlayer()->getSize().x, ResourcesManager::instance().getPlayer()->getSize().y)*0.8/PLAYER_SCALE;
    int numOfCircle = (distance/size) + 1;
    float radius = WINDOW_HEIGHT * 0.02;
    float angleRadians = (m_object.getRotation() + 90.f) * (PI / 180.0f);
    sf::Vector2f currentPosition = m_object.getPosition();
    for(int count = 0; count < numOfCircle; count++) {
        sf::CircleShape tempCircle(radius);
        tempCircle.setPosition(currentPosition);
        tempCircle.setOrigin(radius, radius);
        m_circles.push_back(tempCircle);

        float deltaX = (distance/numOfCircle) * std::cos(angleRadians);
        float deltaY = (distance/numOfCircle) * std::sin(angleRadians);
        currentPosition += sf::Vector2f(deltaX, deltaY);
    }
}

std::vector<sf::CircleShape> Beam::getCircles() const{
    return m_circles;
}

void Beam::move(float time) {
    animate();
    sf::Vector2f direction(-1,0);
    m_object.move(direction*time);
    for(auto &point : m_circles)
        point.move(direction*time);
}

void Beam::handleCollision(Object& object) {
    if (&object != this) {
        object.handleCollision(*this);
    }
}

void Beam::handleCollision(Player& player) {
    player.handleCollision(*this);
}

void Beam::draw(sf::RenderWindow* window) {
    window->draw(m_object);
}
