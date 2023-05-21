#include "ResourcesManager.h"
#include "Values.h"

ResourcesManager::ResourcesManager() {

    sf::Texture titleTex;
    if (!titleTex.loadFromFile(PATH + "Title.png")) {
        throw OpenTextureFailed();
    }
    m_titleTex = titleTex;
    m_titleSpr.setTexture(m_titleTex);

    sf::Texture playerTex;
    if (!playerTex.loadFromFile(PATH + "barryDeathElec.png")) {
        throw OpenTextureFailed();
    }
    m_playerTex = playerTex;
    m_playerSpr.setTexture(m_playerTex);


    for(int index = 0; index < 4; index++){
        if(!m_buttonsTex[index].loadFromFile(PATH + buttons[index])){
            throw OpenTextureFailed();
        }
        m_buttonsSpr[index].setTexture(m_buttonsTex[index]);
    }
}

ResourcesManager &ResourcesManager::inctance() {
    try{
        static ResourcesManager m_instance;
        return m_instance;
    } catch (std::exception& e){
        e.what();
    }
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

sf::Sprite ResourcesManager::getButtonsSpr(int index) const {
    return m_buttonsSpr[index];
}

sf::Texture ResourcesManager::getButtonsTex(int index) const {
    return m_buttonsTex[index];
}

sf::Texture& ResourcesManager::getPlayerTestTex() const {
    return *m_playerTestTex;
}