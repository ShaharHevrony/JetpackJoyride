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
    void draw();
    int getVol();
    void setTopText();

private:
    sf::RenderWindow* m_window;
    sf::Sprite m_settingBoard;

    sf::Text m_topText[5];
    sf::RectangleShape m_topBoard[5];
    int m_topScore[5];

    sf::Sprite m_backButton;
    sf::Text m_backText;

    AudioManager m_music;
    AudioManager m_sound;
};
