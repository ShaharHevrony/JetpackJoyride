#pragma once
#include "Player.h"
#include "Coins.h"

class PlayGame {
public:
    PlayGame(sf::RenderWindow& window);
    ~PlayGame(){}
    void create();
    void run();
    void draw();


    static sf::Clock gameTime;

private:
    float m_backgroundX = 0.0f;
    sf::Sprite m_background[3];
    sf::Texture m_backgroundTex;
    sf::Sprite m_backgroundStartSpr;
    sf::RenderWindow* m_window;
    std::shared_ptr<Player> m_player;
    std::shared_ptr<Coins> m_coin;
    float m_wigthBackSize;
    //bool m_firsTime = true;
    float m_loopTime = 0;
    bool m_start = true;
};
