#pragma once
#include <SFML/Graphics.hpp>

class PlayGame;

class Animation {
public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    Animation(){}
    ~Animation(){}
    void Update(int row);
    sf::IntRect getObjRec();

private:
    sf::IntRect m_objRec;
    sf::Vector2u m_imageCount;
    sf::Vector2u m_currentImage;
    sf::Clock animationClock;

    float m_totalTime;
    float m_switchTime;
};