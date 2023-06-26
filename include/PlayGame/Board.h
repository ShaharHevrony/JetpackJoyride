#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <set>

#include "ResourcesManager.h"
#include "PlayerStateManager.h"
#include "NonCollisionObject.h"

class Board {
public:
    Board();
    ~Board();
    void readObjectFile(int index);
    void writeObjectFile();
    void moveBackgrounds();
    void randMap();
    float getTime() const;
    float getMovement() const;
    void setClock();
    void draw(sf::RenderWindow* window);

    std::vector<std::string> getMap() const;
    sf::Sprite getFirstBackground() const;
    std::vector<sf::Sprite> getBackgrounds() const;
    void setFirstBackground();
    void setBackgrounds(int size);

private:
    static sf::Clock speedIncreaseTimer;

    int m_random = 0;
    sf::Clock m_loopClock = sf::Clock();  //Clock to measure loop time
    float m_speed = 320.f;
    float m_time  = 0.f;
    std::unordered_set<int> m_mapCount;
    std::vector<sf::Sprite> m_backgrounds;
    sf::Sprite m_firstBackground;
    std::vector<std::string> m_map;
    std::set<std::vector<std::string>> m_allMaps;
};
