#include "ResourcesManager.h"

ResourcesManager::ResourcesManager() {

    sf::Texture titleTex;
    if (!titleTex.loadFromFile(PATH + "Title.png")) {
        //TODO: throw
    }
    m_titleTex = titleTex;
    m_titleSpr.setTexture(m_titleTex);
}

ResourcesManager &ResourcesManager::inctance() {
    static ResourcesManager m_instance;
    return m_instance;
}

sf::Sprite ResourcesManager::getTitle() const {
    return m_titleSpr;
}