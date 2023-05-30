#pragma once
#include <SFML/Graphics.hpp>
#include "ResourcesManager.h"
#include "Animation.h"
#include "EventsQueue.h"
#include "box2d/box2d.h"

class Player;
class Obstacle;
class Coin;

class Object {
public:
    Object(sf::Texture* texture = nullptr, const sf::Vector2f& position = sf::Vector2f(0,0));
    Object(Object& other);
    virtual ~Object();
    void animate();
    sf::Sprite& getObject();
    void setSprite(sf::Sprite& obj);
    void draw(sf::RenderWindow* window);
    bool getCollided() const;
    bool getDelete() const;
    void setCollided();
    void setDelete();
    void space(){
        float jumpVelocity = -30.0f; // Adjust the jump velocity as needed
        b2Vec2 bodyVelocity = m_body->GetLinearVelocity();
        bodyVelocity.y = jumpVelocity;
        m_body->SetLinearVelocity(bodyVelocity);
        std::cout << "x:" << m_object.getPosition().x << "y:" << m_object.getPosition().y << std::endl;
        b2Vec2 bodyPosition = m_body->GetPosition();
        float bodyAngle = m_body->GetAngle();
        m_object.setPosition(bodyPosition.x * SCALE, bodyPosition.y * SCALE);
        m_object.setRotation(bodyAngle * 180.0f / b2_pi);
    }
    virtual void move(float time) = 0;
    virtual void handleCollision(Object& object) = 0;
    virtual void handleCollision(Player& player) = 0;
    virtual void handleCollision(Obstacle& obstacle) = 0;
    virtual void handleCollision(Coin& coin) = 0;

protected:
    sf::Sprite m_object;
    Animation m_animation;
    b2Body* m_body;
    //const sf::Vector2f& m_position;


private:
    bool m_isDelete = false;
    bool m_collided = false;
};
