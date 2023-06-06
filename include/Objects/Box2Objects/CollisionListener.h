#pragma once
#include <box2d/box2d.h>
#include "Box2Object.h"

class CollisionListener: public b2ContactListener {
public:
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
};
