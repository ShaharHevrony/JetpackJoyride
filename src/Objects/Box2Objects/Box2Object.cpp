#include "Box2Object.h"

//Constructor for Box2Object with only the type parameter
Box2Object::Box2Object(int type) : Object(), m_type(type) {}

//Constructor for Box2Object with texture, position, and type parameters
Box2Object::Box2Object(sf::Texture* texture, const sf::Vector2f& position, int type) : Object(texture, position), m_type(type) {}

//Destructor for Box2Object
Box2Object::~Box2Object() {
    if (m_body != nullptr) {
        b2World* world = m_body->GetWorld();
        world->DestroyBody(m_body);
        m_body = nullptr;
    }
}

//Function to draw the Box2Object on the SFML window
void Box2Object::draw(sf::RenderWindow* window) {
    if (m_body->GetType() == b2_dynamicBody) {
        auto angle = m_body->GetAngle() * ANGLE_CALC;
        m_object.setRotation(angle);
        m_object.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
    }
    window->draw(m_object);
}

//Function to get the Box2D body associated with the Box2Object
b2Body* Box2Object::getBody() {
    return m_body;
}
