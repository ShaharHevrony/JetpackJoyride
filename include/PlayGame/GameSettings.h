#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "Values.h"
#include "Board.h"

class GameSettings {
public:
    GameSettings(sf::RenderWindow& window, Board& board, Control& control);
    ~GameSettings();
    void create();
    bool run(int playerType);

private:
    sf::RenderWindow* m_window;
    sf::Sprite m_background;
    sf::Sprite m_gameSettings[3];
    Control m_control;
};
