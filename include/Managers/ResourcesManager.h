
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Values.h"
#include "Exeption.h"

class ResourcesManager {
public:
    static ResourcesManager& instance();
    //Get font
    sf::Font& getFont();
    //Get icon
    sf::Image* getIcon();
    //Get all textures:
    sf::Texture* getGameMenu();
    sf::Texture* getTitle();
    sf::Texture* getPlayer();
    sf::Texture* getCoin();
    sf::Texture* getUpperZappers();
    sf::Texture* getLowerZappers();
    sf::Texture* getZappersBeam();
    sf::Texture* getGameSetting();
    sf::Texture* getGameBackground();
    sf::Texture* getFirstBackground();
    sf::Texture* getFlame();
    sf::Texture* getPiggy();
    sf::Texture* getGlitter();
    sf::Texture* getScientist();
    sf::Texture* getSettingBackGround();
    sf::Texture* getQuitKey();
    sf::Texture* getButtons(int index);
    sf::Texture* getBarryDeath(int index);
    sf::Texture* getMissile(int index);
    sf::Texture* getSuperPower(int index);
    sf::Texture* getHelp(int index);
    sf::Texture* getLights();
    sf::Texture* getSuperPowerRunner();
    sf::Texture* getArrow();
    sf::Texture* getBuy();
    sf::Texture* getWiteArrow();


    sf::Texture* getAvatar(int index);
    //Get all audios:
    sf::SoundBuffer& getSoundCoin();
    sf::SoundBuffer& getSoundZapper();
    sf::SoundBuffer& getSoundMissileLaunch();
    sf::SoundBuffer& getSoundMissileAlarm();
    sf::SoundBuffer& getSoundMissileHit();
    sf::SoundBuffer& getSoundPowerBox();

private:
    ResourcesManager();
    ~ResourcesManager();
    //Define font
    sf::Font     m_font;
    //Define icon
    sf::Image   m_icon;
    //Define all textures:
    sf::Texture m_gameMenu;
    sf::Texture m_title;
    sf::Texture m_player;
    sf::Texture m_coin;
    sf::Texture m_upperZappers;
    sf::Texture m_lowerZapper;
    sf::Texture m_zappersBeam;
    sf::Texture m_gameSetting;
    sf::Texture m_gameBackground;
    sf::Texture m_gameFirstBackground;
    sf::Texture m_flame;
    sf::Texture m_piggy;
    sf::Texture m_glitter;
    sf::Texture m_scientist;
    sf::Texture m_settingBackground;
    sf::Texture m_quit;
    sf::Texture m_buttons[8];
    sf::Texture m_barryDeath[2];
    sf::Texture m_missile[3];
    sf::Texture m_superPower[3];
    sf::Texture m_lights;
    sf::Texture m_SuperPowerRunner;
    sf::Texture m_arrow;
    sf::Texture m_whitewArrow;
    sf::Texture m_playerAva[2];
    sf::Texture m_help[3];


    sf::Texture m_buy;


    //Define all audios:
    sf::SoundBuffer m_soundCoin;
    sf::SoundBuffer m_soundZapper;
    sf::SoundBuffer m_soundMissileSound;
    sf::SoundBuffer m_soundMissileAlarm;
    sf::SoundBuffer m_soundMissileHit;
    sf::SoundBuffer m_soundGetPower;
};