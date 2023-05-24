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
    sf::Texture getPlayerTex() const;
    sf::Sprite getButtonsSpr(int index) const;
    sf::Texture getButtonsTex(int index) const;

private:
    ResourcesManager();
    sf::Texture m_backgroundTex;
    sf::Sprite m_backgroundSpr;

    sf::Texture m_titleTex;
    sf::Sprite m_titleSpr;

    sf::Texture m_playerTex;
    sf::Sprite m_playerSpr;

    sf::Texture m_buttonsTex[4];
    sf::Sprite m_buttonsSpr[4];
};