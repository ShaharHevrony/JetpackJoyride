#pragma once
#include <iostream>

const std::string PATH = "../../../";
//const std::string PATH = "";

enum Buttons{
    PlayButton,
    ShopButton,
    SettingButton,
    HelpButton,
};
const std::vector<std::string> buttons = {"PlayGameButton.png", "ShopButton.png", "SettingButton.png", "HelpButton.png"};

const int WINDOW_HEIGHT   = 920;
const int WINDOW_WIDTH    = 1898;
const int SCREEN_CENTER   = WINDOW_WIDTH / 2;
const int MENU_START_ROW  = WINDOW_HEIGHT / 2;
const int MENU_GAP        = 150;
const int MENU_PIC_WIDTH  = 420;
const int MENU_PIC_HEIGHT = 133;
const int TITLE_WIDTH     = 700;
const int TITLE_HEIGHT    = 404;
const float SPEED         = 300.f;
const int NUM_OF_COIN_VEC = 2;

const std::vector<std::vector<sf::Vector2f>> COINS_LOC = {
        {sf::Vector2f(0, 440), sf::Vector2f(40, 490), sf::Vector2f(80, 530), sf::Vector2f(120, 570),
         sf::Vector2f(160, 610), sf::Vector2f(200, 650), sf::Vector2f(240, 690), sf::Vector2f(280, 730),
         sf::Vector2f(20, 110), sf::Vector2f(60, 150), sf::Vector2f(100, 190), sf::Vector2f(140, 230),
         sf::Vector2f(180, 270), sf::Vector2f(220, 310), sf::Vector2f(260, 350), sf::Vector2f(300, 390),},
        {sf::Vector2f(20, 100), sf::Vector2f(20, 160), sf::Vector2f(20, 220), sf::Vector2f(20, 280),
         sf::Vector2f(20, 340), sf::Vector2f(20, 400), sf::Vector2f(20, 460),
         sf::Vector2f(600, 100), sf::Vector2f(600, 160), sf::Vector2f(600, 220), sf::Vector2f(600, 280),
         sf::Vector2f(600, 340), sf::Vector2f(600, 400), sf::Vector2f(600, 460)},
};
