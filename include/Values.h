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

struct ControlGame {
    bool Start_t = true;
    sf::Clock LoopClock_t = sf::Clock(); //Clock to measure loop time
    float ElapsedTime_t = 0.0f;
    float ChangeInterval_t = 5.0f;
    float SpeedTime_t = 0.0f;
    float BackgroundSpeed_t = 0.0f;
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
const int BACKGROUND      = 3;
const int NUM_OF_COIN_VEC = 2;

const float SPEED         = 300.f;

const std::vector<std::vector<sf::Vector2f>> COINS_LOC = {
        {    {
        sf::Vector2f(100, 100),
        sf::Vector2f(200, 200),
        sf::Vector2f(300, 300),
        sf::Vector2f(400, 400),
    },
    {
        sf::Vector2f(500, 500),
        sf::Vector2f(600, 600),
        sf::Vector2f(700, 700),
        sf::Vector2f(800, 800),
    },
    }
};

const int NUM_OF_OBJECTS  = 15;
const char SPACE          = '-';
const char COIN           = '*';
const char OBSTACLE       = '<';

const std::vector<std::string> MAP = { "---***---***---\n"
                                       "---***---***---\n"
                                       "---***---***---\n"
                                       "-*************-\n"
                                       "--***********--\n"
                                       "---*********---\n"
                                       "----*******----\n"
                                       "-----*****-----\n"
                                       "------***------\n"
                                       "-------*-------",

                                       "---------------\n"
                                       "-<----******---\n"
                                       "----******-----\n"
                                       "-<----******---\n"
                                       "----******---<-\n"
                                       "---------------\n"
                                       "-------------<-\n"
                                       "--<------<-----\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---*****-------",

                                       "---*****-------\n"
                                       "--*******------\n"
                                       "-**-----**-----\n"
                                       "**-------**----\n"
                                       "**--------**---\n"
                                       "-**--------**--\n"
                                       "--**--------**-\n"
                                       "---**--------**\n"
                                       "--**--------**-\n"
                                       "-**--------**--\n"
                                       "**--------**---\n"
                                       "**-------**----\n"
                                       "-**-----**-----\n"
                                       "--*******------\n"
                                       "---*****-------",

                                       "--------**---**\n"
                                       "--------**---**\n"
                                       "---------**-**-\n"
                                       "----------***--\n"
                                       "**---**----*---\n"
                                       "**---**--------\n"
                                       "-**-**---------\n"
                                       "--***----------\n"
                                       "---*-----------\n"
                                       "--------**---**\n"
                                       "--------**---**\n"
                                       "---------**-**-\n"
                                       "----------***--\n"
                                       "**---**----*---\n"
                                       "**---**--------\n"
                                       "-**-**---------\n"
                                       "--***----------\n"
                                       "---*-----------",

                                       "----------****-\n"
                                       "---------****--\n"
                                       "--------****---\n"
                                       "-------****----\n"
                                       "------****-----\n"
                                       "-----****------\n"
                                       "----****-------\n"
                                       "---****--------\n"
                                       "--****---------\n"
                                       "-****----------\n"
                                       "****-----------",

                                       "****-----------\n"
                                       "-****----------\n"
                                       "--****---------\n"
                                       "---****--------\n"
                                       "----****-------\n"
                                       "-----****------\n"
                                       "------****-----\n"
                                       "-------****----\n"
                                       "--------****---\n"
                                       "---------****--\n"
                                       "----------****-\n"
                                       "-----------****"  };

/*
const std::string MAP = "---------------\n"
                        "---------------\n"
                        "---------------\n"
                        "-*-----------*-\n"
                        "-*-----------*-\n"
                        "-*************-\n"
                        "-*-----------*-\n"
                        "-*-----------*-\n"
                        "---------------\n"
                        "---------------\n"
                        "---------------\n"
                        "---------------\n"
                        "---------------\n"
                        "-----**--------\n"
                        "----*---*------\n"
                        "---*-----*-----\n"
                        "--*-------*----\n"
                        "--*--------*---\n"
                        "---*--------*--\n"
                        "----*--------*-\n"
                        "-----*--------*\n"
                        "----*--------*-\n"
                        "---*--------*--\n"
                        "--*--------*---\n"
                        "--*-------*----\n"
                        "---*-----*-----\n"
                        "----*---*------\n"
                        "-----**--------\n"
                        "---------------\n"
                        "---------------\n"
                        "---------------\n"
                        "---------------\n"
                        "---------------\n"
                        "-*--------*----\n"
                        "-*----------*--\n"
                        "-*-----------*-\n"
                        "-*----------*--\n"
                        "-***********---\n"
                        "-*-------------\n"
                        "-*-------------\n"
                        "-*-------------\n"
                        "---------------\n"
                        "---------------\n"
                        "-*************-\n"
                        "-*-----*-----*-\n"
                        "-*-----*-----*-\n"
                        "-*-----*-----*-\n"
                        "-*-----*-----*-\n"
                        "---------------\n"
                        "---------------\n"
                        "-*-------------\n"
                        "-*-------------\n"
                        "-*-------------\n"
                        "-*************-\n"
                        "-*-------------\n"
                        "-*-------------\n"
                        "-*-------------\n"
                        "---------------\n"
                        "---------------\n"
                        "-*************-\n"
                        "-*--------*----\n"
                        "-*--------*----\n"
                        "--*------*-----\n"
                        "---*----*------\n"
                        "-----**--------\n"
                        "---------------\n"
                        "---------------\n"
                        "-------------*-\n"
                        "----------**---\n"
                        "-------**-*----\n"
                        "----**----*----\n"
                        "-**-------*----\n"
                        "----**----*----\n"
                        "-------**-*----\n"
                        "----------**---\n"
                        "-------------*-\n"
                        "---------------\n"
                        "---------------\n"
                        "-----***-------\n"
                        "---**-----**---\n"
                        "-*-----------*-\n"
                        "-*-----------*-\n"
                        "-*-----------*-\n"
                        "-*-----------*-\n"
                        "---------------\n"
                        "---------------\n"
                        "-*************-\n"
                        "-------*-------\n"
                        "------*-*------\n"
                        "-----*---*-----\n"
                        "----*-----*----\n"
                        "---*-------*---\n"
                        "--*---------*--\n"
                        "-*-----------*-\n"
                        "---------------\n"
                        "---------------\n"
                        "---------------\n"
                        "---------------\n"
                        "---------------\n"
                        "---------------\n"
                        "-*--------*----\n"
                        "-*----------*--\n"
                        "-*-----------*-\n"
                        "-*----------*--\n"
                        "-***********---\n"
                        "-*-------------\n"
                        "-*-------------\n"
                        "-*-------------\n"
                        "---------------\n"
                        "------***------\n"
                        "----*-----*----\n"
                        "---*-------*---\n"
                        "--*---------*--\n"
                        "-*-----------*-\n"
                        "-*-----------*-\n"
                        "-*-----------*-\n"
                        "-*-----------*-\n"
                        "--*---------*--\n"
                        "---*-------*---\n"
                        "----*-----*----\n"
                        "------***------\n"
                        "---------------\n"
                        "---------------\n"
                        "-*-------------\n"
                        "--**-----------\n"
                        "----**---------\n"
                        "------**-------\n"
                        "--------******-\n"
                        "------**-------\n"
                        "----**---------\n"
                        "--**-----------\n"
                        "-*-------------\n"
                        "---------------\n"
                        "---------------\n"
                        "-*************-\n"
                        "-*-----*-------\n"
                        "-*------*------\n"
                        "-*-------*-----\n"
                        "-*------*-*----\n"
                        "-*-----*---*---\n"
                        "--*---*-----*--\n"
                        "---**--------*-\n"
                        "---------------\n"
                        "---------------\n"
                        "-*-----------*-\n"
                        "-*-----------*-\n"
                        "-*************-\n"
                        "-*-----------*-\n"
                        "-*-----------*-\n"
                        "---------------\n"
                        "---------------\n"
                        "-*************-\n"
                        "-*-----------*-\n"
                        "-*-----------*-\n"
                        "-*-----------*-\n"
                        "--*---------*--\n"
                        "---**-----**---\n"
                        "-----****------\n"
                        "---------------\n"
                        "---------------\n"
                        "-*************-\n"
                        "-*-----*-----*-\n"
                        "-*-----*-----*-\n"
                        "-*-----*-----*-\n"
                        "-*-----*-----*-\n"
                        "---------------\n"
                        "---------------\n"
                        "---------------\n"
                        "-**********--*-\n"
                        "-**********--*-\n"
                        "---------------";
*/