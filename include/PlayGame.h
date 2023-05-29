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

class PlayGame {
public:
    PlayGame(sf::RenderWindow& window);
    ~PlayGame();
    void create();
    void createBarry();
    void createObjectMap();
    void run();
    void dealWithCollision();
    void moveObjects();
    void draw();

private:
    static sf::Clock gameTime;

    ControlGame m_control;
    sf::RenderWindow* m_window;
    Player m_player;
    Board m_board;
    std::vector<std::unique_ptr<Object>> m_singleObjects;
    std::vector<std::unique_ptr<PairedObject>> m_pairedObjects;
};