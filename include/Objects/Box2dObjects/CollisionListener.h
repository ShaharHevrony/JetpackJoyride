#pragma once
#include "box2d/box2d.h"
#include "Box2dObject.h"

class CollisionListener: public b2ContactListener {
public:
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

    int getContactCount() const;
    void setContactCount (int count);
    bool getConnected() const;
    void setConnected(bool contact);

private:
    int m_contactCount = 0;
    bool m_currConnected = false;
    bool m_prevConnected = false;
};
