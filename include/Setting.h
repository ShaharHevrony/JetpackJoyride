#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>

#include "Values.h"
#include "ResourcesManager.h"
#include "AudioManager.h"

class Setting {
public:
    Setting(sf::RenderWindow& window);
    ~Setting();
    void create();
    void run();
    void checkPotentialBest(int score);
    void sort();
    void draw();

    void readFile();
    void writeFile();

private:
    sf::RenderWindow* m_window;
    sf::RenderTexture m_renderTexture;
    sf::RectangleShape m_settingBoard;

    sf::Text m_topText[5];
    sf::RectangleShape m_topBoard[5];
    int m_topScore[5];

    AudioManager m_music;
    AudioManager m_sound;
};
