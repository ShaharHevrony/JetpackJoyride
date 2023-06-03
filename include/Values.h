#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_set>

const std::string PATH = "../../../";
//const std::string PATH = "";

enum Buttons {
    PlayButton,
    ShopButton,
    SettingButton,
    HelpButton,
};

enum EventsTypes {
    CollectedMoney,
    DeathInTheAir,
    DeadOnTheGround,
};

enum Box2Objects{
    FloorType,
    CeilingType,
    PlayerType,
    DeadPlayerType,
};

struct ControlGame {
    std::unordered_set<int> RandomCount_t;
    sf::Clock LoopClock_t = sf::Clock(); //Clock to measure loop time
    float Speed_t = 320.f;
    float Time_t = 0.f;
};

const char SPACE    = '-';
const char COIN     = '*';
const char OBSTACLE = '<';

const float WINDOW_HEIGHT   = sf::VideoMode::getDesktopMode().height * 0.9;
const float WINDOW_WIDTH    = sf::VideoMode::getDesktopMode().width * 0.9;

const float WIDTH_CENTER    = WINDOW_WIDTH  / 2;
const float HEIGHT_CENTER   = WINDOW_HEIGHT / 2;
const float PLAYER_POS_X    = WINDOW_WIDTH  / 10;
const float PLAYER_POS_Y    = WINDOW_HEIGHT / 10;

const float SET_SCALE       = WINDOW_HEIGHT / 1200;
const float SET_OBJ_SCALE   = WINDOW_HEIGHT / 1000;
const float TITLE_POSITION  = WINDOW_HEIGHT / 4.7;
const float MENU_GAP        = WINDOW_HEIGHT / 7.7;

const float SETTING_CIRCLE  = WINDOW_WIDTH  / 100;
const float SETTING_WIDTH   = WINDOW_WIDTH  / 2;
const float SETTING_HEIGHT  = WINDOW_HEIGHT / 1.2;
const float SETTING_SIZE    = WINDOW_WIDTH  / 35;

const float START_POINT     = WINDOW_WIDTH  / 100;
const float SET_BACKGROUND  = WINDOW_HEIGHT / 900;
const float OBJECT_MAP_POS  = WINDOW_WIDTH  / 30;

const float GRAVITATION_Y   = WINDOW_HEIGHT / 500;
const float GRAVITATION_X   = 0.0;
const float DEATH_GRAVITY_Y = WINDOW_HEIGHT / 1500;
const float DEATH_GRAVITY_X = WINDOW_WIDTH  / 7500;
const float BERRYS_MASS     = WINDOW_HEIGHT / 100;
const float BERRYS_FRICTION = WINDOW_WIDTH / 150;
const float TIME_STEP       = 1 / (7 * GRAVITATION_Y);

const float RESIZE_BUTTONS  = 1.15;
const int NUM_OF_BUTTONS    = 4;
const int BACKGROUND        = 3;
const int NUM_OF_OBJECTS    = 15;
const int COLLECTED_MONEY   = 5;
const int TOP_FIVE          = 5;
const double PI             = 3.14159265358;

const sf::Vector2f DEFAULT_VEC = sf::Vector2f(0.f,0.f);

const std::vector<std::string> buttons = {"PlayGameButton.png", "ShopButton.png", "SettingButton.png", "HelpButton.png"};
const std::vector<std::string> scoreBoard = {"MONEY: ","TIME: ", "BEST: "};

const std::vector<std::string> MAP = { "--****---****--\n"
                                       "--****---****--\n"
                                       "--****---****--\n"
                                       "--****---****--\n"
                                       "--****---****--\n"
                                       "***************\n"
                                       "-*************-\n"
                                       "--***********--\n"
                                       "---*********---\n"
                                       "----*******----\n"
                                       "-----*****-----\n"
                                       "------***------\n"
                                       "-------*-------",

                                       "----***--------\n"
                                       "---*****-------\n"
                                       "--***-***------\n"
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
                                       "--***-***------\n"
                                       "---*****-------\n"
                                       "----***--------",

                                       "-------**----**\n"
                                       "-------**----**\n"
                                       "-------**----**\n"
                                       "-------**----**\n"
                                       "--------**--**-\n"
                                       "---------****--\n"
                                       "----------**---\n"
                                       "**----**-------\n"
                                       "**----**-------\n"
                                       "**----**-------\n"
                                       "**----**-------\n"
                                       "-**--**--------\n"
                                       "--****---------\n"
                                       "---**----------\n"
                                       "-------**----**\n"
                                       "-------**----**\n"
                                       "-------**----**\n"
                                       "-------**----**\n"
                                       "--------**--**-\n"
                                       "---------****--\n"
                                       "----------**---\n"
                                       "**----**-------\n"
                                       "**----**-------\n"
                                       "**----**-------\n"
                                       "**----**-------\n"
                                       "-**--**--------\n"
                                       "--****---------\n"
                                       "---**----------",

                                       "----------*****\n"
                                       "---------*****-\n"
                                       "--------*****--\n"
                                       "-------*****---\n"
                                       "------*****----\n"
                                       "-----*****-----\n"
                                       "----*****------\n"
                                       "---*****-------\n"
                                       "--*****--------\n"
                                       "-*****---------\n"
                                       "*****----------",

                                       "*****----------\n"
                                       "-*****---------\n"
                                       "--*****--------\n"
                                       "---*****-------\n"
                                       "----*****------\n"
                                       "-----*****-----\n"
                                       "------*****----\n"
                                       "-------*****---\n"
                                       "--------*****--\n"
                                       "---------*****-\n"
                                       "----------*****",

                                       "-------*-------\n"
                                       "------***------\n"
                                       "-----*****-----\n"
                                       "----**---**----\n"
                                       "---**-----**---\n"
                                       "--**-------**--\n"
                                       "-**---------**-\n"
                                       "**-----------**\n"
                                       "-**---------**-\n"
                                       "--**-------**--\n"
                                       "---**-----**---\n"
                                       "----**---**----\n"
                                       "-----*****-----\n"
                                       "------***------\n"
                                       "-------*-------\n"
                                       "------***------\n"
                                       "-----*****-----\n"
                                       "----**---**----\n"
                                       "---**-----**---\n"
                                       "--**-------**--\n"
                                       "-**---------**-\n"
                                       "**-----------**\n"
                                       "-**---------**-\n"
                                       "--**-------**--\n"
                                       "---**-----**---\n"
                                       "----**---**----\n"
                                       "-----*****-----\n"
                                       "------***------\n"
                                       "-------*-------",

                                       "--------------\n"
                                       "---<----------\n"
                                       "--------------\n"
                                       "--------------\n"
                                       "----------<---\n"
                                       "--------------",

                                       "--------------\n"
                                       "-<----******--\n"
                                       "----******----\n"
                                       "-<----******--\n"
                                       "----******---<\n"
                                       "--------------\n"
                                       "-------------<\n"
                                       "--------------\n"
                                       "--<------<----\n"
                                       "--------------\n"
                                       "----------<---\n"
                                       "-----<--------\n"
                                       "---*****----<-",

                                       "-****-----****-\n"
                                       "-****-----****-\n"
                                       "-****-----****-\n"
                                       "-----*****-----\n"
                                       "-----*****-----\n"
                                       "-----*****-----\n"
                                       "-****-----****-\n"
                                       "-****-----****-\n"
                                       "-****-----****-\n"
                                       "-----*****-----\n"
                                       "-----*****-----\n"
                                       "-----*****-----"  };
/*

const std::string MAP = "--------------\n"
                        "--------------\n"
                        "--------------\n"
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