#pragma once
#include <memory>
#include <fstream>
#include <filesystem>
#include <SFML/Graphics.hpp>

#include "Values.h"
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
    sf::Sprite m_shopeBoard;
    sf::Text m_nameCharacter[4];


};
