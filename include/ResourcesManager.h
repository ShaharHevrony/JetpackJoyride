#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Values.h"

class ResourcesManager{
public:
    static ResourcesManager& inctance();
    sf::Sprite getTitle() const;
    sf::Sprite getPlayerSpr() const;
    sf::Texture getPlayerTex() const;

private:
    ResourcesManager();

    sf::Texture m_titleTex;
    sf::Sprite m_titleSpr;

    sf::Texture m_playerTex;
    sf::Sprite m_playerSpr;
};