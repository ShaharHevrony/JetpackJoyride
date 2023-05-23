#pragma once
#include "Player.h"

class PlayGame {
public:
    PlayGame(sf::RenderWindow& window);
    ~PlayGame(){}
    void create();
    void run();

    static sf::Clock gameTime;

private:
    sf::RenderWindow* m_window;
    std::shared_ptr<Player> m_player;
};
