#pragma once
#include <memory>
#include <fstream>
#include <filesystem>
#include <vector>
#include <ctime>

#include "GameSettings.h"
#include "Laser.h"
#include "ScoreBoard.h"
#include "EventsQueue.h"
#include "Bound.h"
#include "Beam.h"
#include "CollisionListener.h"
#include "Missile.h"
#include "Piggy.h"
#include "SuperPower.h"
#include "GameManager.h"
#include "NonCollisionObject.h"

class PlayGame {
public:
    PlayGame(sf::RenderWindow& window);
    ~PlayGame();
    void create();
    void createObjectMap();
    void createNonCollisionObjects();
    void run();
    void dealWithCollision();
    void dealWithEvent();
    void moveObjects();
    void deathMovement();
    void draw();
    int randMap();

private:
    sf::RenderWindow* m_window;

    sf::Clock m_timer; //Timer to track elapsed time
    sf::Clock m_collisionTimer;

    Board m_board;
    ScoreBoard m_scoreBoard;
    Control m_control;
    CollisionListener m_collisionBox2D;
    sf::Sprite m_settingButton;
    sf::Vector2f m_lastObject = sf::Vector2f(0.f, 0.f);
    sf::Vector2f m_lastCoin   = sf::Vector2f(0.f, 0.f);

    std::vector<std::unique_ptr<Object>> m_singleObjects;
    std::vector<std::unique_ptr<Missile>> m_missile;
    std::vector<std::unique_ptr<Laser>> m_pairedObjects;
    std::shared_ptr<Flame> m_flame;

    b2World* m_world;
    std::shared_ptr<Box2Object> m_player;
    std::unique_ptr<Box2Object> m_floor;
    std::unique_ptr<Box2Object> m_ceiling;
    std::vector<std::unique_ptr<Box2Object>> m_fallingCoins;
    std::vector<std::unique_ptr<NonCollisionObject>> m_nonCollision;
};