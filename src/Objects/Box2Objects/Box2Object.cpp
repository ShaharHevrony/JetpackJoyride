#include "Box2Object.h"

Box2Object::Box2Object(b2World *world, int type) : Object(), m_type(type){}

Box2Object::Box2Object(sf::Texture* texture, const sf::Vector2f& position, b2World* world, int type) :Object(texture, position), m_type(type){}

Box2Object::~Box2Object() {
    if (m_body != nullptr) {
        b2World* world = m_body->GetWorld();
        world->DestroyBody(m_body);
        m_body = nullptr;
    }
}
b2Body* Box2Object::getBody() {
    return m_body;
}

int Box2Object::getType() const {
    return m_type;
}