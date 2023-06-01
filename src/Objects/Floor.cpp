
#include "Floor.h"

Floor::Floor(std::unique_ptr<b2World> *world) : Object(){
    createSquareBody(world->get(),b2_staticBody);
}

void Floor::createSquareBody(b2World *world, b2BodyType bodyType, sf::Vector2i rect) {
    //BodyDef
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(WINDOW_WIDTH / 2,WINDOW_HEIGHT);

    m_body = world->CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(WINDOW_WIDTH,100.f);

    // FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    if (bodyType == b2_dynamicBody) {
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.2f;
    }
    m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);
}
