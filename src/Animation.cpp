
#include "Animation.h"

Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime)
    :m_imageCount(imageCount), m_switchTime(switchTime){
    m_totalTime = 0.f;
    m_currentImage.x = 0;

    m_objRect.width  = texture->getSize().x / float(imageCount.x);
    m_objRect.height = texture->getSize().y / float(imageCount.y);
}

void Animation::Update(int row, float timeDiff) {
    m_currentImage.y = row;
    m_totalTime += timeDiff;

    if (m_totalTime >= m_switchTime) {
        m_totalTime -= m_switchTime;
        m_currentImage.x++;

        if (m_currentImage.x >= m_imageCount.x) {
            m_currentImage.x = 0;
        }
    }

    
    m_objRect.top = m_currentImage.y * m_objRect.height;
    m_objRect.left = m_currentImage.x * m_objRect.width;
    //if(reverseDirection){
      //  m_objRect.width = -abs(m_objRect.width);
    //} else {
      //  m_objRect.width = abs(m_objRect.width);
    //}
   // m_objRect.width = (reverseDirection ? -1 : +1)* abs(m_objRect.width);
}


