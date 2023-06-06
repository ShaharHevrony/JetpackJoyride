
#include "Events/Event.h"

Event::Event() {}

Event::Event(EventsTypes type, int points, const sf::Vector2f& position):m_eventType(type), m_points(points), m_piggyPosition(position) {}

Event::~Event() {}

int Event::getPoints() const {
    return m_points;
}

sf::Vector2f Event::getPiggyPosition() const {
    return m_piggyPosition;
}

EventsTypes Event::getEventType() const {
    return m_eventType;
}