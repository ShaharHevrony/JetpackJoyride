#pragma once
#include "Event.h"
#include <queue>

class EventsQueue {
public:
    static EventsQueue &instance();
    void push(Event event);
    Event pop();
    bool empty();

private:
    EventsQueue();
    ~EventsQueue();
    std::queue<Event> m_events;
};
