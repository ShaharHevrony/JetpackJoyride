#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <filesystem>

#include "Values.h"
#include "ResourcesManager.h"

class Setting {
public:
    Setting(sf::RenderWindow& window);
    ~Setting();
    void create();
    void run();
    void draw();
    void readFile();
    void writeFile();
    void sortTopFive();
    void checkNewRecord(int score);
    void calculatePercentage();
private:
    sf::RenderWindow* m_window;
    sf::RenderTexture m_renderTexture;
    sf::RectangleShape m_settingBoard;
    settingBar m_music;
    settingBar m_sound;
    sf::RectangleShape m_topBoard[5];
    sf::Text m_topText[5];
    int m_topScore[5] = {1405, 40321, 4932, 20494, 20135};
};


