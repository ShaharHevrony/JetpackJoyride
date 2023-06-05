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
#include "Beam.h"
#include "CollisionListener.h"
#include "Missile.h"
#include "Piggy.h"
#include "Flame.h"

class PlayGame {
public:
    PlayGame(sf::RenderWindow& window);
    ~PlayGame();
    void create();
    void createObjectMap();
    void run();
    void dealWithCollision();
    void dealWithEvent();
    void moveObjects();
    void deathMovement(bool& berryState);
    void draw();
    int randMap();
    void displayGameOverScreen();

private:
    sf::Clock m_timer;          //Timer to track elapsed time
    bool m_gameOver = false;    //Flag to indicate if the game is over

    bool m_restartGame = false;
    Board m_board;
    ScoreBoard m_scoreBoard;
    ControlGame m_control;

    sf::RenderWindow* m_window;

    std::unique_ptr<Object> lastObject;
    std::unique_ptr<Flame> m_flame;
    std::vector<std::unique_ptr<Object>> m_singleObjects;
    std::vector<std::unique_ptr<Missile>> m_missile;
    std::vector<std::unique_ptr<PairedObject>> m_pairedObjects;
    std::unique_ptr<b2World> m_world;
    std::unique_ptr<Box2dObject> m_player;
    std::unique_ptr<Box2dObject> m_floor;
    std::unique_ptr<Box2dObject> m_ceiling;
    CollisionListener m_collisionBox2D;

    bool m_missileState;        // Tracks the current state of the missile
    float m_currPosition;
    
};