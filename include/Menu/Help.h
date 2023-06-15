#pragma once
#include <SFML/Graphics.hpp>

#include "Values.h"
#include "GameManager.h"
#include "ResourcesManager.h"

class Help {
public:
    Help(sf::RenderWindow& window);
    ~Help();
    void run();
    void create();
    void draw();

private:
    sf::RenderWindow* m_window;
    std::vector<sf::Sprite> m_HelpBoard ;
    sf::Sprite m_backButton;
    sf::Sprite m_leftArrow;
    sf::Sprite m_rightArrow;

    int m_helpNum = 0;
};
