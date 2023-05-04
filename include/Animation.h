#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/Texture.hpp>
//#include <SFML/System/Vector2.hpp>

class Animation {
public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Animation(){}
    void Update(int row, float timeDiff);

    sf::IntRect m_objRect;
private:

    sf::Vector2u m_imageCount;
    sf::Vector2u m_currentImage;

    float m_totalTime;
    float m_switchTime;
};
