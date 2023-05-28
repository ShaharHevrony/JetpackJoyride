#pragma once

#include <memory>
#include <fstream>
#include <filesystem>
#include <vector>

#include "Player.h"
#include "Coins.h"
#include "Board.h"

class Obstacle;

class PlayGame {
public:
    PlayGame(sf::RenderWindow& window);
    ~PlayGame(){}
    void create();
    void run();
    void draw();
    void createCoin();
    void createBarry();
    void createObstical();
    void createBackGround();
    void dealWithCollision();
    void readObjectFile();
    void writeObjectFile();

    static sf::Clock gameTime;

private:
    float m_backgroundX = 0.0f;
    sf::Sprite m_background[3];
    sf::Sprite m_firstBackground;
    sf::RenderWindow* m_window;
    Player m_player;
    Obstacle m_obstacle;
    Obstacle m_obstacleOpposite;
    float m_widthBackSize;
    bool m_start = true;
    std::vector<std::string> m_map;
    std::vector<std::vector<Coins>> m_objectMap;
};