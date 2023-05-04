#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Values.h"

class ResourcesManager{
public:
    static ResourcesManager& inctance();
    sf::Sprite getTitle() const;

private:
    ResourcesManager();

    sf::Texture m_titleTex;
    sf::Sprite m_titleSpr;

};