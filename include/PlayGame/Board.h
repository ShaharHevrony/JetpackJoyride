#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_set>
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
    void animate();
    void randMap();
    float getTime() const;
    float getMovement() const;
    void setClock();
    void draw(sf::RenderWindow* window);
    std::vector<std::string> getMap() const;
    void setBackgrounds();
    void moveNonColl(bool);

private:
    static sf::Clock loopClock; //Clock to measure loop time

    float m_speedIncrease = 0.f;
    int m_random = 0;
    float m_speed = 320.f;
    float m_time  = 0.f;
    std::unordered_set<int> m_mapCount;
    std::vector<sf::Sprite> m_backgrounds;
    sf::Sprite m_firstBackground;
    std::vector<std::string> m_map;
    std::vector<std::unique_ptr<NonCollisionObject>> m_nonCollLights;
    std::vector<std::unique_ptr<NonCollisionObject>> m_nonCollScis;

    std::set<std::vector<std::string>> m_allMaps;
};