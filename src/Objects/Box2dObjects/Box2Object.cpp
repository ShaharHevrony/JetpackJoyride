
#include "Box2dObject.h"

Box2dObject::Box2dObject(std::unique_ptr<b2World>* world, int type): Object(), m_type(type){}

Box2dObject::Box2dObject(sf::Texture *texture, const sf::Vector2f &position, std::unique_ptr<b2World> *world, int type)
        :Object(texture, position), m_type(type) {}

b2Body* Box2dObject::getBody() {
    return m_body;
}

void Box2dObject::setType(int type) {
    m_type = type;
}

int Box2dObject::getType() const {
    return m_type;
}

void Box2dObject::setSpacePressed(bool pressed){
    m_spacePressed = pressed;
}

bool Box2dObject::getSpacePressed() const{
    return m_spacePressed;
}