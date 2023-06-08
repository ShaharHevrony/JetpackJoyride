#pragma once
#include <memory>
#include <fstream>
#include <filesystem>
#include <SFML/Graphics.hpp>

#include "Values.h"
#include "ResourcesManager.h"
#include "Coin.h"

class Shop {
public:
    Shop(sf::RenderWindow& window);
    ~Shop();
    void create();
    void run(GameControllerInfo& gameController);
    void move();
    void draw(GameControllerInfo& gameController);
private:

    sf::RenderWindow* m_window;
    sf::RectangleShape m_overlay;
    sf::RectangleShape m_shopWindow;
    //sf::Text m_topText[5];

    sf::Sprite m_left;
    sf::Sprite m_right;
    sf::Sprite m_home;
    std::unique_ptr<Coin> m_coin;
    std::unique_ptr<Object> m_avatar;
};
