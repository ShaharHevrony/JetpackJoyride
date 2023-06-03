#pragma once
#include <memory>
#include <fstream>
#include <filesystem>
#include <vector>
#include <ctime>

#include "box2d/box2d.h"
#include "Board.h"
#include "Coin.h"
#include "Obstacle.h"
#include "ScoreBoard.h"
#include "EventsQueue.h"
#include "Player.h"
#include "Bound.h"
#include "CollisionListener.h"

class PlayGame {
public:
    PlayGame(sf::RenderWindow& window);
    ~PlayGame();
    void create();
    void createObjectMap();
    void createBeam(sf::Vector2f position);
    void run();
    void dealWithCollision();
    void dealWithEvent();
    void moveObjects();
    void deathMovement(bool& berryState);
    void draw();
    int randMap();
    double calculateDistance(double x1, double y1, double x2, double y2);
    sf::Vector2f interpolatePosition(const sf::Vector2f& position1, const sf::Vector2f& position2, float t);

private:
    Board m_board;
    ScoreBoard m_scoreBoard;
    ControlGame m_control;

    sf::RenderWindow* m_window;

    std::unique_ptr<Object> lastObject;
    std::vector<std::unique_ptr<Object>> m_singleObjects;
    std::vector<std::unique_ptr<PairedObject>> m_pairedObjects;

    std::unique_ptr<b2World> m_world;
    std::unique_ptr<Box2dObject> m_player;
    std::unique_ptr<Box2dObject> m_floor;
    std::unique_ptr<Box2dObject> m_ceiling;
    CollisionListener m_collisionBox2D;
};