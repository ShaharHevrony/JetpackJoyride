#include "Box2Object.h"

Box2Object::Box2Object(b2World *world, float scale, int type) : Object(), m_type(type), m_scale(scale){}

Box2Object::Box2Object(sf::Texture* texture, const sf::Vector2f& position, b2World* world, float scale, int type)
            :Object(texture, position), m_type(type), m_scale(scale){}

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

void Box2Object::setType(int type) {
    m_type = type;
}

int Box2Object::getType() const {
    return m_type;
}

void Box2Object::setSpacePressed(bool pressed){
    m_spacePressed = pressed;
}

bool Box2Object::getSpacePressed() const{
    return m_spacePressed;
}

bool Box2Object::getSensor() const {
    return m_sensor;
}