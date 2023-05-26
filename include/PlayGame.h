#pragma once
#include "Player.h"
#include "Obstacle.h"
#include "Coins.h"
#include "Board.h"

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
    static sf::Clock gameTime;

private:
    float m_backgroundX = 0.0f;
    sf::Sprite m_background[3];
    sf::Texture m_backgroundTex;
    sf::Sprite m_backgroundStartSpr;
    sf::RenderWindow* m_window;
    Player m_player;
    Obstacle m_obstacle;
    Obstacle m_obstacleOpposite;
    int m_coinsGroup = 0;
    float m_widthBackSize;
    bool m_start = true;
    std::vector<std::vector<Coins>> m_allCoins;
};