#pragma once
#include "box2d/box2d.h"

#include "Object.h"
#include "Coin.h"
#include "Obstacle.h"

class TempPlayer :public Object{
public:
    TempPlayer(sf::Texture* texture, sf::Vector2f position, std::unique_ptr<b2World>* world);
    virtual ~TempPlayer() = default;
    void create(b2World *world, float radius);
    void createSensor(b2World* world, float width, float height, b2Vec2 center, int data);
    void playAnimationOnce(sf::Texture* tempTex);
    void moveRightDown();


    virtual void space();
    virtual void move(float time) {}
    virtual void handleCollision(Object& object);
    virtual void handleCollision(Player& player);
    virtual void handleCollision(Obstacle& obstacle);
    virtual void handleCollision(Coin& coin);
    virtual void draw(sf::RenderWindow* window);


};
