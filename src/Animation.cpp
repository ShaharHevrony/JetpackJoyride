#include "Animation.h"
#include "iostream"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
        :m_imageCount(imageCount), m_switchTime(switchTime) {
    animationClock.restart().asSeconds();
    m_totalTime = 0.f;
    m_currentImage.x = 0;

    m_objRec.width  = texture->getSize().x / float(imageCount.x);
    m_objRec.height = texture->getSize().y / float(imageCount.y);
    //std::cout << "##in c-tor:\ntexture->getSize().x = " << texture->getSize().x << ", texture->getSize().y = " << texture->getSize().x << "\n";
    //std::cout << "imageCount.x = " << imageCount.x << ", imageCount.y = " << imageCount.y << "\n";
    //std::cout << "Therefore:\n\ttexture->getSize().x / float(imageCount.x) = m_objRec.width = " << m_objRec.width
    //<< "\n\ttexture->getSize().y / float(imageCount.y) = m_objRec.height = " << m_objRec.height << "\n";
}

void Animation::Update(int row) {
    float timeDiff = animationClock.restart().asSeconds();
    m_currentImage.y = row;
    m_totalTime += timeDiff;
    //std::cout << "\n##in update:\nm_currentImage.y = row = " << m_currentImage.y << " , m_totalTime = " << m_totalTime << "\n";
    if (m_totalTime >= m_switchTime) {
        m_totalTime -= m_switchTime;
        m_currentImage.x++;
        std::cout << "m_totalTime >= m_switchTime! therefore:\n\tm_totalTime = " << m_totalTime << " , m_currentImage.x = " << m_currentImage.x;
        if (m_currentImage.x >= m_imageCount.x) {
            std::cout << "\n\tm_currentImage.x >= m_imageCount.x! therefore m_currentImage.x os now 0\n\n";
            m_currentImage.x  = 0;
        }
    }
    m_objRec.top  = m_currentImage.y * m_objRec.height;
    m_objRec.left = m_currentImage.x * m_objRec.width;
    //std::cout << "\n\tm_objRec.top = " << m_objRec.top << " , m_objRec.left = " << m_objRec.left;
}

sf::IntRect Animation::getObjRec() {
    return m_objRec;
}
