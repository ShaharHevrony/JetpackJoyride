#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

const std::string PATH = "../../../";
//const std::string PATH = "";

//------------------------------ Enums definitions ------------------------------
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
    DeadPlayer,
    GameOver,
    SuperPowerTank,
    SuperPowerRunner,
};

enum SuperPowersTypes {
    Box,
    WalkingTank,
    FlyingTank,
    Runner,
};

//------------------------------ Consts definitions -----------------------------
//Box2D:
const int32 VELOCITY_ITERATIONS = 6;
const int32 POSITION_ITERATIONS = 2;

//Chars:
const char COIN       = '*';
const char LASER      = '<';
const char MISSILE    = '!';
const char PIGGY      = '$';
const char SUPERPOWER = '@';

//Floats:
const float WINDOW_HEIGHT   = sf::VideoMode::getDesktopMode().height * 0.9;
const float WINDOW_WIDTH    = sf::VideoMode::getDesktopMode().width  * 0.9;

const float WIDTH_CENTER    = WINDOW_WIDTH  / 2;
const float HEIGHT_CENTER   = WINDOW_HEIGHT / 2;
const float TITLE_POSITION  = WINDOW_HEIGHT / 5;
const float WIDTH_GAP       = WINDOW_WIDTH  / 8;
const float HEIGHT_GAP      = WINDOW_HEIGHT / 4;
const float SET_BUTTONS     = WINDOW_HEIGHT / 1050;
const float SHOP_POS_X      = 8 * WINDOW_WIDTH / 10;
const float SHOP_POS_Y      = WINDOW_HEIGHT / 10;
const float GAME_SETTING_X  = 11 * WINDOW_WIDTH / 12;
const float GAME_SETTING_Y  = WINDOW_HEIGHT / 12;

const float SETTING_CIRCLE  = WINDOW_WIDTH  / 100;
const float SETTING_HEIGHT  = WINDOW_HEIGHT / 20;
const float SETTING_SIZE    = WINDOW_WIDTH  / 35;

const float PLAYER_SCALE    = WINDOW_HEIGHT / 1200;
const float OBJECT_SCALE    = WINDOW_HEIGHT / 1000;

const float PLAYER_POS_X    = WINDOW_WIDTH  / 5;
const float PLAYER_POS_Y    = WINDOW_HEIGHT / 4;
const float CEILING_POS_X   = WINDOW_HEIGHT / 5;
const float FLOOR_POS_X     = WINDOW_HEIGHT / 14;

const float VELOCITY_DELTA  = 3 / WINDOW_HEIGHT;
const float GRAVITATION_Y   = WINDOW_HEIGHT / 1500;
const float GRAVITATION_X   = 0.f;
const float DEATH_GRAVITY_Y = GRAVITATION_Y / 3;
const float DEATH_GRAVITY_X = GRAVITATION_Y / 10;
const float MASS            = WINDOW_HEIGHT / 1000;
const float FRICTION        = WINDOW_WIDTH  / 70;
const float TIME_STEP       = GRAVITATION_Y / 10;

const float DEFAULT_SPEED   = 0.18f;
const float LAST_POSITION   = -50.f;
const float FASTER_SPEED    = 1.2f;
const float ANTI_GRAVITY    = -9.f;
const float CHANGE_INTERVAL = 2.5f;
const float ACCELERATION    = 35.f;
const float MINUTE          = 60.f;
const float ANGLE_CALC      = 180.0f / b2_pi;

//Integers:
const int NUM_OF_BUTTONS    = 4;
const int BACKGROUND        = 3;
const int GAME_SETTINGS     = 3;
const int NUM_OF_OBJECTS    = 15;
const int COLLECTED_MONEY   = 1;
const int COLLECTED_PIGGY   = 10;
const int COLLECTED_SUPER   = 30;
const int TOP_FIVE          = 5;
const int BUTTON_NUM = 8;
const int BUTTON_NUM_DIV_TWO = 4;
const int DIV_TWO = 2;
const int THIRD = 3;
const int ZERO = 0;
const int FIRST = 1;
const int SECOND = 2;
const int FOUR = 4;
const int SIX = 6;
const int SEVEN = 7;
const int TEN = 10;
const int TWENTY = 20;
const int TWENTY_SIX = 26;
const int EIGHTY = 80;
const int HUNDRED = 100;
const int ONE_TWENY_EIGHT = 128;
const int ONE_FIFTHY = 150;
const int ONE_EIGHTY_INT = 180;
const int TWO_HUNDRED = 200;
const int THREE_HUNDRED = 300;
const int TWO_FIFTHY_FIVE = 255;
const float TWO_POINT_O = 2.0;
const float ONE_POINT_FIVE = 1.5;
const float ONE_POINT_ZERO = 1.0;
const float ONE_POINT_TWO = 1.2;
const float ONE_POINT_THIRTY_FIVE = 1.35;
const float ZERO_POINT_FIVE = 0.5;
const float ZERO_POINT_ONE_TWO = 0.12;
const float ONE_EIGHTY = 180.0;
const float NINETY = 90.0;
const float TWO_SEVENTY = 270.0;
const float THREE_SIXTY = 360.0;
const float ZERO_POINT_TWO_TWO = 0.22;
const float ZERO_POINT_ZERO_TWO = 0.02;
const float ZERO_POINT_ONE = 0.1;
const float FIVE_F = 5;
const float THREE_F = 3;
const float FOUR_F = 4;
const float ONE_POINT_EIGHT = 1.8;
const float ONE_POINT_ONE_EIGHT = 1.18;
const float ZERO_POINT_EIGHT = 0.8;
const float ZERO_POINT_THREE = 0.3;
const float ZERO_POINT_SEVEN = 0.7;
const float ZERO_POINT__ONE_EIGHT = 0.18;
const float ONE_POINT_TWO_EIGHT = 1.28;











//Double:
const double PI             = 3.14159265358;

//SFML:
const sf::Vector2f DEFAULT_VEC       = sf::Vector2f(0.f,0.f);
const sf::Vector2f DIRECTION         = sf::Vector2f (-1,0);
const sf::Vector2u DEFAULT_ANIMATION = sf::Vector2u(4,1);
//Vectors:
const std::vector<int> prices                  = {0, 520, 760, 1100};
const std::vector<std::string> scoreBoard      = {"MONEY: ","TIME: ", "BEST: "};
const std::vector<std::string> squareNames     = {"Berry", "King","Scientist" , "Soldier"};

const std::vector<std::string> buttons         = {"PlayGameOff.png", "ShopOff.png", "SettingsOff.png", "HelpOff.png", "PlayGameOn.png", "ShopOn.png", "SettingsOn.png", "HelpOn.png"};
const std::vector<std::string> missile         = {"MissileWarning.png","MissileIncoming.png", "Missile.png"};
const std::vector<std::string> superPower      = {"PowerUpBox.png", "SuperPowerTank.png" ,"SuperPowerFlyTank.png", "SuperPowerRunner.png"};
const std::vector<std::string> help            = {"HelpMenuOne.png", "HelpMenuTwo.png" , "HelpMenuThree.png"};
const std::vector<std::string> settingsButtons = {"Resume.png", "Retry.png", "SettingQuit.png"};
const std::vector<std::string> playersAvatar   = {"BerryAvatar.png", "ScientistAvatar.png" ,"SoldierAvatar.png", "KingAvatar.png"};
const std::vector<std::vector<std::string>> playerStates = {{"BerryWalking.png", "BerryHit.png", "BerryDead.png"},
                                                            {"ScientistWalking.png", "ScientistHit.png", "ScientistDead.png"},
                                                            {"SoldierWalking.png", "SoldierHit.png", "SoldierDead.png"},
                                                            {"KingWalking.png", "KingHit.png", "KingDead.png"}};

const std::vector<std::string> MAP = { "--*---------*--\n"
                                       "--*---------*--\n"
                                       "---*-------*---\n"
                                       "----*-----*<---\n"
                                       "-----*---*-----\n"
                                       "------*-*------\n"
                                       "-------*-------\n"
                                       "------*-*------\n"
                                       "-----*---*-<---\n"
                                       "----*-----*----\n"
                                       "---*-------*---\n"
                                       "--*------!--*--\n"
                                       "--*---------*--\n"
                                       "--*--------*---\n"
                                       "---*------*----\n"
                                       "--<-*----*-----\n"
                                       "-----*--*------\n"
                                       "------**-------\n"
                                       "------**-------\n"
                                       "-----*--*------\n"
                                       "----*----*-----\n"
                                       "--<*------*----\n"
                                       "---*-------*---\n"
                                       "--*---------*--\n"
                                       "--*---------*--\n"
                                       "---*--------*--\n"
                                       "----*------*---\n"
                                       "-----*----*----\n"
                                       "------*--*-----\n"
                                       "-------**------\n"
                                       "-------**------\n"
                                       "---!---$-------",

                                       "--*--*---*--*--\n"
                                       "--*--*---*--*--\n"
                                       "--*--*---*--*--\n"
                                       "--*--*---*--*--\n"
                                       "--*--*---*--*--\n"
                                       "--***********--\n"
                                       "--***********--\n"
                                       "--**-------**--\n"
                                       "---**-----**---\n"
                                       "-<--**---**----\n"
                                       "-----**-**-----\n"
                                       "------***------\n"
                                       "-------*-------\n"
                                       "---<---$-------",

                                       "----***-<-----<\n"
                                       "---**-**-------\n"
                                       "--**---**------\n"
                                       "-**-----**-----\n"
                                       "**-------**----\n"
                                       "**--------**---\n"
                                       "-**----<---**--\n"
                                       "--**--------**-\n"
                                       "---**--------**\n"
                                       "--**--------**-\n"
                                       "-**----<---**--\n"
                                       "**--------**---\n"
                                       "**-------**----\n"
                                       "-**-----**-----\n"
                                       "--**---**------\n"
                                       "---**-**-------\n"
                                       "----***----!---" ,

                                       "-------**----**\n"
                                       "-------**----**\n"
                                       "-------**----**\n"
                                       "-------**----**\n"
                                       "--------**--**-\n"
                                       "---------****--\n"
                                       "----------**---\n"
                                       "**----**-------\n"
                                       "**----**--<----\n"
                                       "**----**-------\n"
                                       "**----**-------\n"
                                       "-**--**--------\n"
                                       "--****---------\n"
                                       "---**-----<----\n"
                                       "---------------\n"
                                       "-----**----**--\n"
                                       "-----**----**--\n"
                                       "-----**----**--\n"
                                       "-----**----**--\n"
                                       "------**--**---\n"
                                       "-------****----\n"
                                       "--------**-----\n"
                                       "---------------\n"
                                       "--**----**-----\n"
                                       "--**----**--<--\n"
                                       "--**----**-----\n"
                                       "--**----**-----\n"
                                       "---**--**---<--\n"
                                       "----****------\n"
                                       "-----**----!---" ,

                                       "----------*****\n"
                                       "---------*****-\n"
                                       "--<-----*****--\n"
                                       "-------*****---\n"
                                       "------*****----\n"
                                       "-----*****-----\n"
                                       "--<-*****------\n"
                                       "---*****---@---\n"
                                       "--*****--------\n"
                                       "-*****---------\n"
                                       "*****----------\n"
                                       "----------*****\n"
                                       "---------*****-\n"
                                       "--------*****--\n"
                                       "-------*****---\n"
                                       "------*****----\n"
                                       "-----*****-----\n"
                                       "----*****---<--\n"
                                       "---*****-------\n"
                                       "--*****--------\n"
                                       "-*****---------\n"
                                       "*****-!-----<--",

                                       "*****----------\n"
                                       "-*****---------\n"
                                       "--*****---!----\n"
                                       "---*****-------\n"
                                       "----*****------\n"
                                       "-----*****-----\n"
                                       "--<---*****----\n"
                                       "-------*****---\n"
                                       "--------*****--\n"
                                       "---------*****-\n"
                                       "--<-------*****",

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
                                       "-----*****---<-\n"
                                       "------***------\n"
                                       "-------*-------\n"
                                       "------***------\n"
                                       "-----*****-----\n"
                                       "----**---**--<-\n"
                                       "---**-----**---\n"
                                       "--**---<---**--\n"
                                       "-**---------**-\n"
                                       "**-----------**\n"
                                       "-**---------**-\n"
                                       "--**---<---**--\n"
                                       "---**-----**---\n"
                                       "----**---**----\n"
                                       "-----*****-----\n"
                                       "------***------\n"
                                       "-------$-------" ,

                                       "------<------<-\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "----**---------\n"
                                       "---****--------\n"
                                       "---*****-------\n"
                                       "----*****------\n"
                                       "---*****-------\n"
                                       "---****--------\n"
                                       "----**---------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "*-------------*\n"
                                       "**-----------**\n"
                                       "***---------***\n"
                                       "****-------****\n"
                                       "***---------***\n"
                                       "**-----------**\n"
                                       "*-------------*\n"
                                       "------$--------\n"
                                       "---------------\n"
                                       "-<-------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "-<-------------\n"
                                       "--------**-----\n"
                                       "-------****----\n"
                                       "-------*****---\n"
                                       "--------*****--\n"
                                       "-------*****---\n"
                                       "-------****----\n"
                                       "--------**-----\n"
                                       "---------------\n"
                                       "----------<----\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "----------<----\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "-----***-------\n"
                                       "-----***-------\n"
                                       "-----***-------",

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
                                       "--****---****--\n"
                                       "--*--*---*--*--\n"
                                       "--*--*@--*--*--\n"
                                       "--*--*---*--*--\n"
                                       "--*--*---*--*--\n"
                                       "--***********--\n"
                                       "***************\n"
                                       "-**---------**-\n"
                                       "--**-------**--\n"
                                       "---**-----**---\n"
                                       "----**---**----\n"
                                       "-----**-**-----\n"
                                       "------***------\n"
                                       "-------*-------\n"
                                       "-------$-------\n"
                                       "---------------\n"
                                       "---------------\n"
                                       "-----<---------\n"
                                       "------------<--\n"
                                       "---------------",

                                       "--<------------\n"
                                       "---------------\n"
                                       "-------------*-\n"
                                       "-------------*-\n"
                                       "-------------*-\n"
                                       "------------*--\n"
                                       "-----------*---\n"
                                       "----------*----\n"
                                       "--<------*-----\n"
                                       "--------*------\n"
                                       "-------*-------\n"
                                       "------*--------\n"
                                       "-----*---------\n"
                                       "----*----------\n"
                                       "---*-----------\n"
                                       "--*--------<---\n"
                                       "-*-------------\n"
                                       "*--------------\n"
                                       "-*-------------\n"
                                       "--*------------\n"
                                       "---*-------<---\n"
                                       "----*----------\n"
                                       "-----*---------\n"
                                       "------*--------\n"
                                       "--<----*-------\n"
                                       "--------*------\n"
                                       "---------*-----\n"
                                       "----------*----\n"
                                       "-----------*---\n"
                                       "--<---------*--\n"
                                       "-------------*-\n"
                                       "--------------*\n"
                                       "-------@-----*-\n"
                                       "------------*--\n"
                                       "-----------*---\n"
                                       "----------*----\n"
                                       "---------*-----\n"
                                       "--------*------\n"
                                       "-------*-------\n"
                                       "------*--------\n"
                                       "-----*---------\n"
                                       "----*--------<-\n"
                                       "---*-----------\n"
                                       "--*------------\n"
                                       "-*----<--------\n"
                                       "*--------------\n"
                                       "-*-------------\n"
                                       "--*------------\n"
                                       "---*-----------\n"
                                       "----*----------\n"
                                       "-----*------!--\n"
                                       "------*--------\n"
                                       "-------*-------\n"
                                       "---<----*------\n"
                                       "---------*-----\n"
                                       "----------*----\n"
                                       "-----------*---\n"
                                       "------------*--\n"
                                       "-------------*-\n"
                                       "--------------*\n"
                                       "-------------*-\n"
                                       "------------*--\n"
                                       "-----------*---\n"
                                       "---<------*----\n"
                                       "---------*-----\n"
                                       "--------*------\n"
                                       "-------*-------\n"
                                       "------*--------\n"
                                       "-----*---------\n"
                                       "----*----------\n"
                                       "---*-----------\n"
                                       "---$-----------", };