#pragma once
#include "Objects/Player.h"
class PlayGame {
public:
    PlayGame(sf::RenderWindow& window);
    ~PlayGame(){}
    void create();
    void run();
    //void killBarry();

private:
    sf::RenderWindow* m_window;
    std::shared_ptr<Player> m_player;
};
