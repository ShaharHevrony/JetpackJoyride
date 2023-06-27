#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>

#include "Values.h"
#include "ResourcesManager.h"
#include "AudioManager.h"

class Settings {
public:
    Settings(sf::RenderWindow& window);
    ~Settings();
    void create();
    void run();
    void draw();
    void setTopText();

private:
    sf::RenderWindow* m_window;
    sf::Sprite m_settingBoard;

    sf::Text m_topText[TOP_FIVE];
    sf::RectangleShape m_topBoard[TOP_FIVE];
    int m_topScore[TOP_FIVE];

    sf::Sprite m_backButton;
    sf::Text m_backText;
    AudioManager m_music;
    AudioManager m_sound;
};
