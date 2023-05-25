#pragma once
#include "Player.h"
#include "TempObj.h"
#include "Coins.h"

class PlayGame {
public:
    PlayGame(sf::RenderWindow& window);
    ~PlayGame(){}
    void create();
    void run();
    void draw();
    void updatePositions();
    //void readObjectFile();
    //void writeObjectFile();

    static sf::Clock gameTime;

private:
    float m_backgroundX = 0.0f;
    sf::Sprite m_background[3];
    sf::Texture m_backgroundTex;
    sf::Sprite m_backgroundStartSpr;
    sf::RenderWindow* m_window;
    Player m_player;
    std::vector<Coins> m_coin;
    std::vector<sf::Vector2f> m_coinPositions;
    float m_widthBackSize;
    bool m_start = true;
    std::vector<std::string> m_map;
    std::vector<std::vector<std::shared_ptr<Coins>>> m_objectMap;
};