#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <set>

#include "box2d/box2d.h"
#include "ResourcesManager.h"

class Board {
public:
    Board();
    ~Board();
    void readObjectFile(int index);
    void writeObjectFile();
    void moveBackgrounds(float time);
    void draw(sf::RenderWindow* window, ControlGame& control);

    std::vector<std::string> getMap(int index) const;
    sf::Sprite getFirstBackground() const;
    std::vector<sf::Sprite> getBackgrounds() const;
    float getWidth() const;
    void setFirstBackground();
    void setBackgrounds(int size);

private:
    std::vector<sf::Sprite> m_backgrounds;
    sf::Sprite m_firstBackground;
    std::vector<std::string> m_map;
    std::set<std::vector<std::string>> m_allMaps;
};
