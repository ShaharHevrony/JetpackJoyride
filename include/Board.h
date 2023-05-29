#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "ResourcesManager.h"
#include "Player.h"

class Board {
public:
    Board();
    ~Board();
    void readObjectFile();
    void writeObjectFile();

    std::vector<std::string> getMap(int index) const;
    sf::Sprite getFirstBackground() const;
    std::vector<sf::Sprite> getBackgrounds() const;
    float getWidth() const;
    void setFirstBackground();
    void setFirstBackgroundPosition(sf::Vector2f position);
    void setBackgrounds(int size);
    void setBackgroundPosition(int index, sf::Vector2f position);

private:
    std::vector<sf::Sprite> m_backgrounds;
    sf::Sprite m_firstBackground;
    std::vector<std::vector<std::string>> m_map;
};
