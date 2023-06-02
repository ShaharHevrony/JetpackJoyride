#include "CollisionListener.h"

void CollisionListener::BeginContact(b2Contact *contact) {
    //Check fixture A
    void* bodyA = contact->GetFixtureA()->GetBody()->GetUserData();
    auto objA   = static_cast<Object*>(bodyA);
    void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();

    //Check fixture B
    void* bodyB = contact->GetFixtureB()->GetBody()->GetUserData();
    auto objB  = static_cast<Object*>(bodyB);
    void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

    if (!objA | !objB) {
        return;
    }
    if (!m_prevConnected){
        m_currConnected = true;
        m_contactCount++;
        m_prevConnected = m_currConnected;
    } else {
        m_currConnected = false;
    }
}

void CollisionListener::EndContact(b2Contact *contact) {
    //check fixture A
    void* bodyA = contact->GetFixtureA()->GetBody()->GetUserData();
    auto objA   = static_cast<Object*>(bodyA);
    void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();

    //check fixture B
    void* bodyB = contact->GetFixtureB()->GetBody()->GetUserData();
    auto objB   = static_cast<Object*>(bodyB);
    void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

    if (!objA | !objB) {
        return;
    }
    m_prevConnected = false;
}

int CollisionListener::getContactCount() const {
    return m_contactCount;
}

void CollisionListener::setContactCount(int count) {
    m_contactCount = count;
}

bool CollisionListener::getConnected() const {
    return m_currConnected;
}

void CollisionListener::setConnected(bool contact) {
    m_currConnected = contact;
}