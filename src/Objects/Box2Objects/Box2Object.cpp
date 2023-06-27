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

void Box2Object::draw(sf::RenderWindow *window) {
    if(m_body->GetType() == b2_dynamicBody) {
        auto angle = m_body->GetAngle() * 180.0f / b2_pi;
        m_object.setRotation(angle);
        m_object.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
    }
    window->draw(m_object);
}

b2Body* Box2Object::getBody() {
    return m_body;
}