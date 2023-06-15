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
    void draw();
    void setAvatar();

private:
    sf::RenderWindow* m_window;
    sf::Sprite m_shopBoard;
    std::vector<sf::Text> m_names;
    //std::vector<sf::RectangleShape> m_characters;
    sf::RectangleShape m_characterRect;
    std::stringstream m_str;
    sf::Text money;
    sf::Sprite m_backButton;
    sf::Sprite m_buyButton;

    sf::Sprite m_leftArrow;
    sf::Sprite m_rightArrow;

    int m_avatarIndex = 0;
    //sf::Text m_prices[2];
    std::vector<sf::Text> m_pricesText;
};
