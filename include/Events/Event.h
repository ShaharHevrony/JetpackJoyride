#pragma once
#include "Values.h"

class Event {
public:
    Event();
    Event(EventsTypes type, int pointsToAdd = 0, const sf::Vector2f& position = DEFAULT_VEC);
    ~Event();
    int getPoints() const;
    sf::Vector2f getPiggyPosition() const;
    EventsTypes getEventType() const;

private:
    int m_points;
    EventsTypes m_eventType;
    sf::Vector2f m_piggyPosition;
};
