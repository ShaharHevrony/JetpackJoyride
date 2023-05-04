#include "ResourcesManager.h"

ResourcesManager::ResourcesManager() {

    sf::Texture titleTex;
    if (!titleTex.loadFromFile(PATH + "Title.png")) {
        //TODO: throw
    }
    m_titleTex = titleTex;
    m_titleSpr.setTexture(m_titleTex);

    sf::Texture playerTex;
    if (!playerTex.loadFromFile(PATH + "Player.png")) {
        //TODO: throw
    }
    m_playerTex = playerTex;
    m_playerSpr.setTexture(m_playerTex);
}

ResourcesManager &ResourcesManager::inctance() {
    static ResourcesManager m_instance;
    return m_instance;
}

sf::Sprite ResourcesManager::getTitle() const {
    return m_titleSpr;
}

sf::Sprite ResourcesManager::getPlayerSpr() const {
    return m_playerSpr;
}

sf::Texture ResourcesManager::getPlayerTex() const{
    return m_playerTex;
}