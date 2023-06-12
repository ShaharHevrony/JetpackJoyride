#include "CollisionListener.h"

void CollisionListener::BeginContact(b2Contact* contact) {
    //Check fixture A
    void* bodyA = contact->GetFixtureA()->GetBody()->GetUserData();
    auto objA = static_cast<Box2Object*>(bodyA);

    //Check fixture B
    void* bodyB = contact->GetFixtureB()->GetBody()->GetUserData();
    auto objB = static_cast<Box2Object*>(bodyB);

    if (!objA | !objB) {
        return;
    }
}

void CollisionListener::EndContact(b2Contact* contact) {
    //check fixture A
    void* bodyA = contact->GetFixtureA()->GetBody()->GetUserData();
    auto objA = static_cast<Box2Object*>(bodyA);

    //check fixture B
    void* bodyB = contact->GetFixtureB()->GetBody()->GetUserData();
    auto objB = static_cast<Box2Object*>(bodyB);

    if (!objA | !objB) {
        lastContact = false;
        currentContact = true;
        return;
    }
}

bool CollisionListener::getContact() const {
    return currentContact;
}
