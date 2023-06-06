#include "CollisionListener.h"

void CollisionListener::BeginContact(b2Contact *contact) {
    //Check fixture A
    void* bodyA  = contact->GetFixtureA()->GetBody()->GetUserData();
    auto objA    = static_cast<Box2Object*>(bodyA);
    bool sensorA = objA->getSensor();
    //Check fixture B
    void* bodyB = contact->GetFixtureB()->GetBody()->GetUserData();
    auto objB   = static_cast<Box2Object*>(bodyB);
    bool sensorB = objB->getSensor();

    if (!objA | !objB) {
        return;
    }
    else if(sensorA || sensorB){

    }

}

void CollisionListener::EndContact(b2Contact *contact) {
    //check fixture A
    void* bodyA = contact->GetFixtureA()->GetBody()->GetUserData();
    auto objA   = static_cast<Box2Object*>(bodyA);
    void* fixtureUserDataA = contact->GetFixtureA()->GetUserData(); //Help to find witch two object collided

    //check fixture B
    void* bodyB = contact->GetFixtureB()->GetBody()->GetUserData();
    auto objB   = static_cast<Box2Object*>(bodyB);
    void* fixtureUserDataB = contact->GetFixtureB()->GetUserData(); //Help to find witch two object collided

    if (!objA | !objB) {
        return;
    }
}