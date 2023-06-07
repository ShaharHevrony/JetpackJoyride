#pragma once
#include <memory>
#include <fstream>
#include <filesystem>
#include <vector>
#include <ctime>
#include <box2d/box2d.h>

#include "GameSettings.h"
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
    std::vector<std::unique_ptr<PairedObject>> m_pairedObjects;
    std::unique_ptr<Flame> m_flame;

    b2World* m_world;
    std::unique_ptr<Box2Object> m_player;
    std::unique_ptr<Box2Object> m_floor;
    std::unique_ptr<Box2Object> m_ceiling;
    std::vector<std::unique_ptr<Box2Object>> m_fallingCoins;
};