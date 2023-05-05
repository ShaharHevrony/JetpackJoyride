#pragma once

class PlayGame {
public:
    PlayGame(sf::RenderWindow& window);
    ~PlayGame(){}
    void create();
    void run();
    void killBarry();

private:
    sf::RenderWindow* m_window;
};


