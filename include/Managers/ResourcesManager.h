#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Values.h"
#include "Exeption.h"

class ResourcesManager{
public:
    static ResourcesManager& instance();
    //Get font
    sf::Font& getFont();
    //Get icon
    sf::Image* getIcon() const;

    //Get all textures:
    sf::Texture* getGameMenu() const;
    sf::Texture* getTitle() const;
    sf::Texture* getPlayer() const;
    sf::Texture* getCoin() const;
    sf::Texture* getUpperZappers() const;
    sf::Texture* getLowerZappers() const;
    sf::Texture* getZappersBeam() const;
    sf::Texture* getGameSetting() const;
    sf::Texture* getGameBackground() const;
    sf::Texture* getFirstBackground() const;
    sf::Texture* getFlame() const;
    sf::Texture* getPiggy() const;
    sf::Texture* getGlitter() const;
    sf::Texture* getScientist() const;
    sf::Texture* getSettingBackGround() const;
    sf::Texture* getQuitKey() const;
    sf::Texture* getButtons(int index) const;
    sf::Texture* getBarryDeath(int index) const;
    sf::Texture* getMissile(int index) const;
    sf::Texture* getSuperPower(int index) const;
    sf::Texture* getLights() const;
    sf::Texture* getSuperPowerRunner() const;



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
    sf::Image*   m_icon;

    //Define all textures:
    sf::Texture* m_gameMenu;
    sf::Texture* m_title;
    sf::Texture* m_player;
    sf::Texture* m_coin;
    sf::Texture* m_upperZappers;
    sf::Texture* m_lowerZapper;
    sf::Texture* m_zappersBeam;
    sf::Texture* m_gameSetting;
    sf::Texture* m_gameBackground;
    sf::Texture* m_gameFirstBackground;
    sf::Texture* m_flame;
    sf::Texture* m_piggy;
    sf::Texture* m_glitter;
    sf::Texture* m_scientist;
    sf::Texture* m_settingBackground;
    sf::Texture* m_quit;
    sf::Texture* m_buttons[8];
    sf::Texture* m_barryDeath[2];
    sf::Texture* m_missile[3];
    sf::Texture* m_superPower[3];
    sf::Texture* m_lights;
    sf::Texture* m_SuperPowerRunner;


    //Define all audios:
    sf::SoundBuffer m_soundCoin;
    sf::SoundBuffer m_soundZapper;
    sf::SoundBuffer m_soundMissileSound;
    sf::SoundBuffer m_soundMissileAlarm;
    sf::SoundBuffer m_soundMissileHit;
    sf::SoundBuffer m_soundGetPower;
};