#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "Values.h"
#include "ResourcesManager.h"
#include "Board.h"

class GameSettings {
public:
    GameSettings(sf::RenderWindow& window, Board& board, ControlGame& control);
    ~GameSettings();
    void create();
    bool run(int playerType);

private:
    sf::RenderWindow* m_window;
    sf::RectangleShape m_overlay;
    sf::RectangleShape m_setting;
    sf::Text m_gameSettings[3];
    Board m_board;
    ControlGame m_control;
};
