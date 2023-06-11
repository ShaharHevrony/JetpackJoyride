#pragma once
#include <SFML/Graphics.hpp>
#include "Values.h"

class Controller {
public:
    Controller();
    ~Controller();
    void run();
    void create();
    void draw();
    void handleMouseButton(sf::Event::MouseButtonEvent& event);
    void handleMouseMoved(sf::Event::MouseMoveEvent& event);
    void setGameControllerInfo(GameControllerInfo gameController);
    GameControllerInfo getGameControllerInfo();

private:
    sf::RenderWindow m_window;
    GameControllerInfo m_gameController;
    sf::Sprite m_menuBackground;
    sf::Sprite m_title;
    std::vector<sf::Sprite> m_gameButtons;
    std::vector<sf::Sprite> m_getButtonSpr;
    int m_buttonToScale = 0;
};