#include "Box2Object.h"

Box2Object::Box2Object(int type) : Object(), m_type(type){}

Box2Object::Box2Object(sf::Texture* texture, const sf::Vector2f& position, int type)
        :Object(texture, position), m_type(type) {
    m_object.setOrigin(m_object.getTextureRect().width/2, m_object.getTextureRect().height/2);
}

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
