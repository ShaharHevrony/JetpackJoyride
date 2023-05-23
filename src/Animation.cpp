#include "Animation.h"

Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime)
        :m_imageCount(imageCount), m_switchTime(switchTime){
    m_totalTime = 0.f;
    m_currentImage.x = 0;

    m_objRec.width  = texture->getSize().x / float(imageCount.x);
    m_objRec.height = texture->getSize().y / float(imageCount.y);
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
    m_objRec.top = m_currentImage.y * m_objRec.height;
    m_objRec.left = m_currentImage.x * m_objRec.width;
}

sf::IntRect Animation::getObjRec() {
    return m_objRec;
}
