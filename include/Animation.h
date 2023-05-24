#pragma once
#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Animation(){}
    void Update(int row, float timeDiff);
    sf::IntRect getObjRec();

private:
    sf::IntRect m_objRec;
    sf::Vector2u m_imageCount;
    sf::Vector2u m_currentImage;

    float m_totalTime;
    float m_switchTime;
};