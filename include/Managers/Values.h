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
    CollectedPiggy,
    startSuperPower,
    ReturnRegular,
};

enum Box2Objects {
    B2Floor,
    B2Ceiling,
    B2Player,
    B2StaticCoin,
    B2DynamicCoin,
};

enum PlayerState {
    Regular,
    SuperPowerTank,
    SuperPowerRunner,
    DeadPlayer,
    GameOver,
};

struct Control {
    std::unordered_set<int> RandomCount_t;
    sf::Clock LoopClock_t = sf::Clock();  //Clock to measure loop time
    float Speed_t = 320.f;
    float Time_t  = 0.f;
};

const char SPACE      = '-';
const char COIN       = '*';
const char LASER      = '<';
const char MISSILE    = '!';
const char PIGGY      = '$';
const char SCIENTIST  = 'S';
const char SUPERPOWER = '@';

const float WINDOW_HEIGHT   = sf::VideoMode::getDesktopMode().height * 0.9;
const float WINDOW_WIDTH    = sf::VideoMode::getDesktopMode().width * 0.9;

const float WIDTH_CENTER    = WINDOW_WIDTH  / 2;
const float HEIGHT_CENTER   = WINDOW_HEIGHT / 2;
const float PLAYER_POS_X    = WINDOW_WIDTH  / 6;
const float PLAYER_POS_Y    = WINDOW_HEIGHT / 4;
const float FLOOR_POS_Y     = WINDOW_HEIGHT / 9;
const float CEILING_POS_Y   = WINDOW_HEIGHT / 10;
const float GAME_SETTING_X  = 11 * WINDOW_WIDTH / 12;
const float SHOP_POS_X      = 8  * WINDOW_WIDTH / 10;
const float SHOP_POS_Y      = WINDOW_HEIGHT / 10;
const float GAME_SETTING_Y  = WINDOW_HEIGHT / 12;

const float PLAYER_SCALE    = WINDOW_HEIGHT / 1200;
const float OBJECT_SCALE    = WINDOW_HEIGHT / 1000;
const float TITLE_POSITION  = WINDOW_HEIGHT / 4.7;
const float MENU_WIDTH_GAP  = WINDOW_WIDTH  / 8;
const float MENU_HEIGHT_GAP = WINDOW_HEIGHT / 4;
const float SET_BUTTONS     = WINDOW_HEIGHT / 250;

const float SETTING_CIRCLE  = WINDOW_WIDTH  / 100;
const float SETTING_WIDTH   = WINDOW_WIDTH  / 2;
const float SETTING_HEIGHT  = WINDOW_HEIGHT / 20;
const float SCALE_SIZE      = WINDOW_WIDTH  / 35;

const float GRAVITATION_Y   = WINDOW_HEIGHT / 500;
const float GRAVITATION_X   = 0.f;
const float DEATH_GRAVITY_Y = WINDOW_HEIGHT / 1500;
const float DEATH_GRAVITY_X = WINDOW_WIDTH  / 7500;
const float BERRYS_MASS     = WINDOW_HEIGHT / 100;
const float COINS_MASS      = WINDOW_HEIGHT / 1000;
const float BERRYS_FRICTION = WINDOW_WIDTH  / 150;
const float TIME_STEP       = 1 / (5 * GRAVITATION_Y);
const float ANTI_GRAVITY    = -10.f;
const int NUM_OF_BUTTONS    = 4;
const int BACKGROUND        = 3;
const int GAME_SETTINGS     = 3;
const int NUM_OF_OBJECTS    = 15;
const int COLLECTED_MONEY   = 5;
const int TOP_FIVE          = 5;
const double PI             = 3.14159265358;

const sf::Vector2f DEFAULT_VEC = sf::Vector2f(0.f,0.f);

const std::vector<std::string> gameSettings = {"Resume", "Restart", "Quit"};
const std::vector<std::string> scoreBoard = {"MONEY: ","TIME: ", "BEST: "};
const std::vector<std::string> playerWalking = {"BerryWalking.png","KingWalking.png", "ScientistWalking.png" , "SoldierWalking.png"};

const std::vector<std::string> buttons     = {"PlayGameOff.png", "ShopOff.png", "SettingsOff.png", "HelpOff.png", "PlayGameOn.png", "ShopOn.png", "SettingsOn.png", "HelpOn.png"};
const std::vector<std::string> missile     = {"MissileWarning.png","MissileIncoming.png", "Missile.png"};
const std::vector<std::string> superPower  = {"PowerUpBox.png", "SuperPowerTank.png" ,"SuperPowerFlyTank.png"};
const std::vector<std::vector<std::string>> berrysDeath = {{"BerryHit.png", "BerryDead.png",},
                                                           {"KingHit.png", "KingDead.png"},
                                                           {"ScientistHit.png", "ScientistDead.png"},
                                                            {"SoldierHit.png", "SoldierDead.png"}};
const std::vector<std::string> squareNames = { "Berry", "King","Scientist" , "Soldier"};
const std::vector<std::string> help        = { "helpone.png", "helptwo.png" , "helpthree.png"};


const std::vector<std::string> playersAvatar = { "BerryAvatar.png", "KingAvatar.png", "ScientistAvatar.png" ,"SoldierAvatar.png"};
const int prices[] = { 0, 2000, 3000, 4000 };


const std::vector<std::string> MAP = { "--*---------*--\n"
                                       "--*---------*--\n"
                                       "---*-------*---\n"
                                       "----*-----*<---\n"
                                       "-----*---*-----\n"
                                       "------*-*------\n"
                                       "-------*-------\n"
                                       "------*-*------\n"
                                       "-----*---*-<---\n"
                                       "----*-----*---S\n"
                                       "---*-------*---\n"
                                       "--*---------*--\n"
                                       "--*---------*--\n"
                                       "--*--------*---\n"
                                       "---*------*----\n"
                                       "--<-*----*-----\n"
                                       "-----*--*------\n"
                                       "------**------S\n"
                                       "------**-------\n"
                                       "-----*--*------\n"
                                       "----*----*-----\n"
                                       "--<*------*----\n"
                                       "---*-------*---\n"
                                       "--*---------*-S\n"
                                       "--*---------*--\n"
                                       "---*--------*--\n"
                                       "----*------*---\n"
                                       "-----*----*----\n"
                                       "------*--*-----\n"
                                       "-------**------\n"
                                       "-------**-----S\n"
                                       "---!---$-------",

                                       "--*--*---*--*--\n"
                                       "--*--*---*--*--\n"
                                       "--*--*@--*--*--\n"
                                       "--*--*---*--*--\n"
                                       "--*--*---*--*--\n"
                                       "--***********--\n"
                                       "--**********--S\n"
                                       "--**-------**--\n"
                                       "---**-----**---\n"
                                       "----**---**----\n"
                                       "-----**-**----S\n"
                                       "------***------\n"
                                       "-------*-------\n"
                                       "-------$-------",

                                       "----***--------\n"
                                       "---**-**-------\n"
                                       "--**---**<----S\n"
                                       "-**-----**-----\n"
                                       "**-------**----\n"
                                       "**--------**---\n"
                                       "-**------<-**--\n"
                                       "--**----@---**-\n"
                                       "---**--------**\n"
                                       "<-**--------**-\n"
                                       "-**--------**--\n"
                                       "**--------**---\n"
                                       "**-------**----\n"
                                       "<**-----**-----\n"
                                       "--**---**------\n"
                                       "---**-**------S\n"
                                       "----***----!---",

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
                                       "--****--------S\n"
                                       "---**----------\n"
                                       "-----**----**--\n"
                                       "-----**----**--\n"
                                       "-----**----**--\n"
                                       "-----**----**--\n"
                                       "------**--**---\n"
                                       "-------****----\n"
                                       "--------**-S---\n"
                                       "--**----**-----\n"
                                       "--**----**-----\n"
                                       "--**----**-----\n"
                                       "--**----**-----\n"
                                       "---**--**------\n"
                                       "----****-------\n"
                                       "-----**----!---",

                                       "----------*****\n"
                                       "--@------*****-\n"
                                       "--<-----*****--\n"
                                       "-------*****---\n"
                                       "------*****---S\n"
                                       "-----*****-----\n"
                                       "----*****------\n"
                                       "---*****---!---\n"
                                       "--<****-------S\n"
                                       "-*****---------\n"
                                       "*****----------\n"
                                       "----------*****\n"
                                       "---------*****-\n"
                                       "--------*****--\n"
                                       "--<----*****---\n"
                                       "------*****---S\n"
                                       "-----*****-----\n"
                                       "--<-*****------\n"
                                       "---*****---!---\n"
                                       "--*****-------S\n"
                                       "-*****---------\n"
                                       "*****----------",

                                       "*****----------\n"
                                       "-*****---------\n"
                                       "--*****---!---S\n"
                                       "---*****-------\n"
                                       "----*****------\n"
                                       "-----*****-----\n"
                                       "------*****---S\n"
                                       "-<-----*****---\n"
                                       "--------*****--\n"
                                       "--<------*****-\n"
                                       "----------*****",

                                       "-------*-------\n"
                                       "---<--***------\n"
                                       "-----*****-----\n"
                                       "----**---**---S\n"
                                       "---**---<-**---\n"
                                       "--**-------**--\n"
                                       "-**---------**-\n"
                                       "**-----------**\n"
                                       "-**---------**-\n"
                                       "--**-------**--\n"
                                       "---**-----**---\n"
                                       "----**-<-**----\n"
                                       "-----*****-----\n"
                                       "------***------\n"
                                       "-------*-------\n"
                                       "------***---<--\n"
                                       "-----*****----S\n"
                                       "-<--**---**----\n"
                                       "---**-----**---\n"
                                       "--**-------**--\n"
                                       "-**-<-------**-\n"
                                       "**-----------**\n"
                                       "-**---------**-\n"
                                       "--**-------**--\n"
                                       "---**-----**---\n"
                                       "----**---**----\n"
                                       "-----*****-----\n"
                                       "<----<***------\n"
                                       "-------*-------",

                                       "-------------<-\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "--**----<------\n"
                                       "-****---------S\n"
                                       "-*****---------\n"
                                       "--*****--------\n"
                                       "-*****---------\n"
                                       "-****----------\n"
                                       "--**-----------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---*****-------\n"
                                       "---*-*-*------S\n"
                                       "--*--*--*------\n"
                                       "-*********-----\n"
                                       "---------------\n"
                                       "--<------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "------<--------\n"
                                       "---------------\n"
                                       "---!-------@---\n"
                                       "---------------\n"
                                       "----****-------\n"
                                       "----****-------\n"
                                       "----****-------\n"
                                       "----****-------\n"
                                       "---------------\n"
                                       "-<------<------\n"
                                       "---------------\n"
                                       "----------$----\n"
                                       "--***---------S\n"
                                       "-*---*-------<-\n"
                                       "*-----*--------\n"
                                       "--***----------\n"
                                       "-------------<-\n"
                                       "------**-------\n"
                                       "------**-------\n"
                                       "------**-------",

                                       "-****-----****-\n"
                                       "-****-----****-\n"
                                       "-****-----****-\n"
                                       "-----*****-----\n"
                                       "-----*****----S\n"
                                       "---@-*****-----\n"
                                       "-****-----****-\n"
                                       "-****-----****-\n"
                                       "-****-----****-\n"
                                       "-----*****----S\n"
                                       "-----*****--!--\n"
                                       "-----*****-----\n"
                                       "---------------\n"
                                       "---<-----<-----\n"
                                       "---------------\n"
                                       "-----*-----@---\n"
                                       "----***--------\n"
                                       "----***--------\n"
                                       "----***--------\n"
                                       "-----*---------\n"
                                       "-------*-------\n"
                                       "------***------\n"
                                       "------***------\n"
                                       "------***------\n"
                                       "-------*-------\n"
                                       "---------------\n"
                                       "--<----<-------\n"
                                       "---------!-----" ,

                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "--------------S\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "--------------S\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "--------------S\n"
                                       "---------------\n"                        
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------" };
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