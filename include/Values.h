#pragma once
#include <iostream>

const std::string PATH = "../../../";
//const std::string PATH = "";

enum Buttons{
    playButton,
    shopButton,
    settingButton,
    helpButton,
};

const int WINDOW_HEIGHT   = 1068;
const int WINDOW_WIDTH    = 1898;
const int SCREEN_CENTER   = WINDOW_WIDTH / 2;
const int MENU_START_ROW  = WINDOW_HEIGHT / 2;
const int MENU_GAP        = 150;
const int MENU_PIC_WIDTH  = 420;
const int MENU_PIC_HEIGHT = 133;
const int TITLE_WIDTH     = 700;
const int TITLE_HEIGHT    = 404;

//"flowtrect"
//const int SPRITE_SCALE = 0.720720720;

const std::vector<std::string> buttons = {"PlayGameButton.png", "ShopButton.png", "SettingButton.png", "HelpButton.png"};