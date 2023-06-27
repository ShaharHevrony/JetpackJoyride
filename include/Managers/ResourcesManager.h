#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Values.h"
#include "Exeption.h"

class ResourcesManager {
public:
    static ResourcesManager& instance();

    //Get font:
    sf::Font& getFont();

    //Get icon:
    sf::Image* getIcon();

    //Get all textures:
    sf::Texture* getGameMenu();
    sf::Texture* getTitle();
    sf::Texture* getCoin();
    sf::Texture* getLaser();
    sf::Texture* getLasersBeam();
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
    sf::Texture* getPlayerStates(int type, int state);
    sf::Texture* getMissile(int index);
    sf::Texture* getSuperPower(int index);
    sf::Texture* getHelp(int index);
    sf::Texture* getLights();
    sf::Texture* getArrow();
    sf::Texture* getBuy();
    sf::Texture* getEquip();
    sf::Texture* getSettingButtons(int index);
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
    //Define font:
    sf::Font m_font;

    //Define icon:
    sf::Image m_icon;

    //Define all textures:
    sf::Texture m_gameMenu;
    sf::Texture m_title;
    sf::Texture m_coin;
    sf::Texture m_laser;
    sf::Texture m_lasersBeam;
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
    sf::Texture m_playerStates[4][3];
    sf::Texture m_missile[3];
    sf::Texture m_superPower[4];
    sf::Texture m_lights;
    sf::Texture m_arrow;
    sf::Texture m_playerAvatar[4];
    sf::Texture m_help[3];
    sf::Texture m_equip;
    sf::Texture m_gameSettingButtons[3];
    sf::Texture m_buy;

    //Define all audios:
    sf::SoundBuffer m_soundCoin;
    sf::SoundBuffer m_soundZapper;
    sf::SoundBuffer m_soundMissileSound;
    sf::SoundBuffer m_soundMissileAlarm;
    sf::SoundBuffer m_soundMissileHit;
    sf::SoundBuffer m_soundGetPower;
};