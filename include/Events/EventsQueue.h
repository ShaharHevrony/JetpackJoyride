#pragma once
#include <queue>
#include "Event.h"

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
