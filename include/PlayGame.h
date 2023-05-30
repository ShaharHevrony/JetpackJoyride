#pragma once
#include <memory>
#include <fstream>
#include <filesystem>
#include <vector>
#include <ctime>

#include "Board.h"
#include "Player.h"
#include "Coin.h"
#include "Obstacle.h"
#include "ScoreBoard.h"
#include "EventsQueue.h"

class PlayGame {
public:
    PlayGame(sf::RenderWindow& window);
    ~PlayGame();
    void create();
    void createBarry();
    void createObjectMap();
    void run();
    void dealWithCollision();
    void dealWithEvent();
    void moveObjects();
    void draw();
    int randMap();
    double calculateDistance(double x1, double y1, double x2, double y2);
    sf::Vector2f interpolatePosition(const sf::Vector2f& position1, const sf::Vector2f& position2, float t);



private:
    static sf::Clock gameTime;
    ControlGame m_control;
    sf::RenderWindow* m_window;
    Player m_player;
    Board m_board;
    ScoreBoard m_scoreBoard;
    std::vector<std::unique_ptr<Object>> m_singleObjects;
    std::vector<std::unique_ptr<PairedObject>> m_pairedObjects;
    std::unique_ptr<Object> lastObject;
    bool m_isDead = false;
};