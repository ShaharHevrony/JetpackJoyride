#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Values.h"
#include "Exeption.h"

class ResourcesManager{
public:
    static ResourcesManager& instance();
    sf::Sprite getTitle() const;
    sf::Sprite getPlayerSpr() const;
    sf::Texture* getPlayerTex() const;
    sf::Sprite getButtonsSpr(int index) const;
    sf::Texture* getCoinTex() const;
    sf::Sprite getCoinSpr() const;
    sf::Texture getButtonsTex(int index) const;
    sf::Sprite getBackground() const;
    sf::Texture getBackgroundTex() const;
    sf::Sprite getBackgroundStartSpr() const;
    sf::Texture getBackgroundStartTex() const;

private:
    ResourcesManager();
    sf::Texture m_backgroundTex;
    sf::Sprite m_backgroundSpr;

    sf::Texture m_titleTex;
    sf::Sprite m_titleSpr;

    sf::Texture* m_playerTex;
    sf::Sprite m_playerSpr;

    sf::Texture m_buttonsTex[4];
    sf::Sprite m_buttonsSpr[4];

    sf::Texture m_backgroundStartTex;
    sf::Sprite m_backgroundStartSpr;

    sf::Texture* m_coinTex;
    sf::Sprite m_coinSpr;
};