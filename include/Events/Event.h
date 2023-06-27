#pragma once
#include "Values.h"
#include "Object.h"

class Event {
public:
    Event();
    Event(EventsTypes type, int pointsToAdd = 0, const sf::Vector2f& position = DEFAULT_VEC);
    ~Event();
    int getPoints() const;
    void setSuper() const;
    std::vector<std::unique_ptr<Object>> createFallingCoins();
    EventsTypes getEventType() const;

private:
    int m_points;
    EventsTypes m_eventType;
    sf::Vector2f m_piggyPosition;
};
