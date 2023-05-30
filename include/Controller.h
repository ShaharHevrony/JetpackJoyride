#pragma once
#include <SFML/Graphics.hpp>

#include "Values.h"

class Controller {
public:
    Controller();
    ~Controller();
    void run();
    void create();
    void handleMouseButton(sf::Event::MouseButtonEvent& event);
    void handleMouseMoved(sf::Event::MouseMoveEvent& event);

private:
    sf::RenderWindow m_window;
    sf::Sprite m_title;
    std::vector<sf::Sprite> m_buttonSpr;
    int m_buttonToScale = 0;
};