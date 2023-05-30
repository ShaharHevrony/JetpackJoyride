#pragma once
#include "Values.h"

class Event {
public:
    Event();
    Event(EventsTypes type, int pointsToAdd = 0);
    ~Event();
    int getPoints() const;
    EventsTypes getEventType() const;

private:
    int m_points;
    EventsTypes m_eventType;
};
