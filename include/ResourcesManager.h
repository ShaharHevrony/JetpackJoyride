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
    sf::Texture* getFirstBackground() const;
    sf::Texture* getBackground() const;
    sf::Texture* getBarryDeath(int index) const;
    sf::Texture* getLiserLine() const;



private:
    ResourcesManager();
    ~ResourcesManager();
    sf::Font     m_font;
    sf::Texture* m_player;
    sf::Texture* m_coin;
    sf::Texture* m_obstacle;
    sf::Texture* m_title;
    sf::Texture* m_buttons[4];
    sf::Texture* m_firstBackground;
    sf::Texture* m_background;
    sf::Texture* m_barryDeath[2];
    sf::Texture* m_laiserLine;


};