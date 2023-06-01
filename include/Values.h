#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_set>

//const std::string PATH = "../../../";
const std::string PATH = "";

enum Buttons{
    PlayButton,
    ShopButton,
    SettingButton,
    HelpButton,
};

enum EventsTypes {
    CollectedMoney,
    Death,
};

struct ControlGame {
    std::unordered_set<int> RandomCount_t;
    sf::Clock LoopClock_t = sf::Clock(); //Clock to measure loop time
    float Speed_t         = 320.f;
    float Time_t          = 0.f;
};

const std::vector<std::string> buttons = {"PlayGameButton.png", "ShopButton.png", "SettingButton.png", "HelpButton.png"};

const std::vector<std::string> barryDeath = {"barryHit.png", "barryDed.png" };

const std::string scoreBoard[3] = {"MONEY: ","TIME: ", "BEST: "};

const int WINDOW_HEIGHT   = sf::VideoMode::getDesktopMode().height * 0.8;
const int WINDOW_WIDTH    = sf::VideoMode::getDesktopMode().width * 0.8;
const int SCREEN_CENTER   = WINDOW_WIDTH / 2;
const int MENU_START_ROW  = WINDOW_HEIGHT / 2;
const int MENU_GAP        = 150;
const int MENU_PIC_WIDTH  = 420;
const int MENU_PIC_HEIGHT = 133;
const int TITLE_WIDTH     = 700;
const int TITLE_HEIGHT    = 404;
const int BACKGROUND      = 3;
const int NUM_OF_OBJECTS  = 14;
const int COLLECTED_MONEY = 5;
const int TOP_FIVE        = 5;
const float SPEED         = 320.f;
const float SCALE         = 30.0f;
const float TIME_STEP     = 1.f;
//const float TIME_STEP     = 120.f;
//const float TIME_STEP     = 1.f;
const float TIME_STEP     = 60.f;


const char SPACE          = '-';
const char COIN           = '*';
const char OBSTACLE       = '<';

const std::vector<std::string> MAP = { "---***---***--\n"
                                       "---***---***--\n"
                                       "---***---***--\n"
                                       "-*************\n"
                                       "--***********-\n"
                                       "---*********--\n"
                                       "----*******---\n"
                                       "-----*****----\n"
                                       "------***-----\n"
                                       "-------*------",

                                       "---****-------\n"
                                       "--******------\n"
                                       "-**----**-----\n"
                                       "**------**----\n"
                                       "**-------**---\n"
                                       "-**-------**--\n"
                                       "--**-------**-\n"
                                       "---**-------**\n"
                                       "--**-------**-\n"
                                       "-**-------**--\n"
                                       "**-------**---\n"
                                       "**------**----\n"
                                       "-**----**-----\n"
                                       "--******------\n"
                                       "---****-------",

                                       "-------**---**\n"
                                       "-------**---**\n"
                                       "--------**-**-\n"
                                       "---------***--\n"
                                       "**---**---*---\n"
                                       "**---**-------\n"
                                       "-**-**--------\n"
                                       "--***---------\n"
                                       "---*---**---**\n"
                                       "-------**---**\n"
                                       "--------**-**-\n"
                                       "---------***--\n"
                                       "**---**---*---\n"
                                       "**---**-------\n"
                                       "-**-**--------\n"
                                       "--***---------\n"
                                       "---*----------",

                                       "----------****\n"
                                       "---------****-\n"
                                       "--------****--\n"
                                       "-------****---\n"
                                       "------****----\n"
                                       "-----****-----\n"
                                       "----****------\n"
                                       "---****-------\n"
                                       "--****--------\n"
                                       "-****---------\n"
                                       "****----------",

                                       "****----------\n"
                                       "-****---------\n"
                                       "--****--------\n"
                                       "---****-------\n"
                                       "----****------\n"
                                       "-----****-----\n"
                                       "------****----\n"
                                       "-------****---\n"
                                       "--------****--\n"
                                       "---------****-\n"
                                       "----------****",

                                       "------**------\n"
                                       "----**--**----\n"
                                       "---**----**---\n"
                                       "--**------**--\n"
                                       "-**--------**-\n"
                                       "**----------**\n"
                                       "-**--------**-\n"
                                       "--**------**--\n"
                                       "---**----**---\n"
                                       "----**--**----\n"
                                       "------**------\n"
                                       "----**--**----\n"
                                       "---**----**---\n"
                                       "--**------**--\n"
                                       "-**--------**-\n"
                                       "**----------**\n"
                                       "-**--------**-\n"
                                       "--**------**--\n"
                                       "---**----**---\n"
                                       "----**--**----\n"
                                       "------**------",

                                       "-***------***-\n"
                                       "-***------***-\n"
                                       "-***------***-\n"
                                       "-----****-----\n"
                                       "-----****-----\n"
                                       "-----****-----\n"
                                       "-***------***-\n"
                                       "-***------***-\n"
                                       "-***------***-\n"
                                       "-----****-----\n"
                                       "-----****-----\n"
                                       "-----****-----"  ,


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
                                       "---*****----<-"};
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