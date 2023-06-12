#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <SFML/Audio.hpp>

#include "Values.h"
#include "GameManager.h"

class Controller {
public:
    Controller();
    ~Controller();
    void run();
    void create();
    void draw();
    void handleMouseButton(sf::Event::MouseButtonEvent& event);
    void handleMouseMoved(sf::Event::MouseMoveEvent& event);

private:
    sf::RenderWindow m_window;
    sf::Sprite m_menuBackground;
    sf::Sprite m_title;
    std::vector<sf::Sprite> m_gameButtons;
    std::vector<sf::Sprite> m_getButtonSpr;

    sf::Music m_music;
    int m_buttonToScale = 0;
    int m_musicSound = 0;

};