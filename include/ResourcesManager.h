#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Values.h"
#include "Exeption.h"

class ResourcesManager{
public:
    static ResourcesManager& instance();
    sf::Font& getFont();
    sf::Texture* getTitle() const;
    sf::Texture* getPlayer() const;
    sf::Texture* getCoin() const;
    sf::Texture* getObstacle() const;
    sf::Texture* getButtons(int index) const;
    sf::Texture* getGameSetting() const;
    sf::Texture* getFirstBackground() const;
    sf::Texture* getBackground() const;
    sf::Texture* getBarryDeath(int index) const;
    sf::Texture* getLaserBeam() const;
    sf::Texture* getMissile(int index) const;
    sf::Texture* getFlame() const;
    sf::Texture* getPiggy() const;
    sf::Texture* getGlitter() const;
    sf::Texture* getScientist() const;
    sf::Texture* getSuperPower(int index) const;

    sf::SoundBuffer& getSoundCoin();
    sf::SoundBuffer& getSoundZapper();
    sf::SoundBuffer& getSoundMissileLaunch();
    sf::SoundBuffer& getSoundMissileAlarm();


   /*
    sf::Texture* getNext() const;
    sf::Texture* getPrev() const;
    sf::Texture* getLock() const;
    sf::Texture* getUnlock() const;
    */

private:
    ResourcesManager();
    ~ResourcesManager();
    sf::Font     m_font;
    sf::Texture* m_player;
    sf::Texture* m_coin;
    sf::Texture* m_obstacle;
    sf::Texture* m_laserBeam;
    sf::Texture* m_piggy;
    sf::Texture* m_title;
    sf::Texture* m_buttons[4];
    sf::Texture* m_gameSetting;
    sf::Texture* m_firstBackground;
    sf::Texture* m_background;
    sf::Texture* m_barryDeath[2];
    sf::Texture* m_missile[3];
    sf::Texture* m_flame;
    sf::Texture* m_glitter;
    sf::Texture* m_scientist;
    sf::Texture* m_superPower[3];

    sf::SoundBuffer m_soundCoin;
    sf::SoundBuffer m_soundZapper;
    sf::SoundBuffer m_soundMissileSound;
    sf::SoundBuffer m_soundMissileAlarm;



    sf::Texture* m_prev;
    sf::Texture* m_next;
    sf::Texture* m_locked;
    sf::Texture* m_unlocked;
};