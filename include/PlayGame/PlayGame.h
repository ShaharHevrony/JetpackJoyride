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
    void run();
    void checkIfNeedToClear();
    void createObjectMap();
    void animateObj();
    void moveObj();
    void dealWithCollision();
    void dealWithEvent();
    void deathMoveObj();
    void deleteObj();
    void draw();

private:
    float m_lastObjectX;
    sf::RenderWindow* m_window;

    sf::Clock m_settingTimer;       //Timer to track elapsed time
    sf::Clock m_collisionTimer;

    Board m_board;
    ScoreBoard m_scoreBoard;
    sf::Sprite m_settingButton;

    std::vector<std::unique_ptr<Object>> m_singleObj;
    std::vector<std::unique_ptr<Object>> m_fallingCoins;
    std::vector<std::unique_ptr<Object>> m_missiles;
    std::vector<std::unique_ptr<Laser>> m_pairedObj;
    std::shared_ptr<NonCollisionObject> m_flame;

    b2World* m_world;
    std::shared_ptr<Box2Object> m_player;
    std::unique_ptr<Box2Object> m_floor;
    std::unique_ptr<Box2Object> m_ceiling;
};