
#include "Events/Event.h"

Event::Event() {}

Event::Event(EventsTypes type, int points):m_eventType(type), m_points(points) {}

Event::~Event() {}

int Event::getPoints() const {
    return m_points;
}

EventsTypes Event::getEventType() const {
    return m_eventType;
}