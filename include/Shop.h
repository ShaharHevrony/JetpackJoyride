#pragma once
#include <memory>
#include <fstream>
#include <filesystem>
#include <SFML/Graphics.hpp>

class Shop {
public:
    Shop(sf::RenderWindow& window){}
    ~Shop(){}
    void create();
    void run();

private:
    sf::RenderWindow* m_window;
};
