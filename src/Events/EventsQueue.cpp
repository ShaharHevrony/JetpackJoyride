#include "EventsQueue.h"

EventsQueue::EventsQueue() {}

EventsQueue::~EventsQueue() {}

EventsQueue &EventsQueue::instance() {
    static EventsQueue events;
    return events;
}

void EventsQueue::push(Event event) {
    m_events.push(event);
}

Event EventsQueue::pop() {
    auto lastEvent = m_events.front();
    m_events.pop();
    return lastEvent;
}

bool EventsQueue::empty() {
    return m_events.empty();
}