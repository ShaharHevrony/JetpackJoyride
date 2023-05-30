#pragma once
#include <SFML/Graphics.hpp>

class PlayGame;

class Animation {
public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    Animation(){}
    ~Animation(){}
    void Update();
    bool hasPlayed() const;
    sf::IntRect getObjRec();

private:
    sf::Clock animationClock;
    bool m_hasPlayed;
    sf::IntRect m_objRec;
    sf::Vector2u m_imageCount;
    sf::Vector2u m_currentImage;

    float m_totalTime;
    float m_switchTime;
};