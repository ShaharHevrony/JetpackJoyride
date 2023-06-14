#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>

#include "Values.h"
#include "GameManager.h"
#include "ResourcesManager.h"

class Shop {
public:
    Shop(sf::RenderWindow& window);
    ~Shop();
    void create();
    void run();
    void move();
    void draw();

private:
    sf::RenderWindow* m_window;
    sf::Sprite m_shopBoard;
    std::vector<sf::Text> m_names;
    std::vector<sf::RectangleShape> m_characters;
    std::stringstream m_str;
    sf::Text money;
    sf::Sprite m_backButton;

};
