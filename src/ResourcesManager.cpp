#include "ResourcesManager.h"
#include "Values.h"

ResourcesManager::ResourcesManager() {
    sf::Texture* playerTex = new sf::Texture();
    if (!playerTex->loadFromFile(PATH + "Player.png")) {
        //throw OpenTextureFailed();
    }
    m_playerTex = playerTex;
    m_playerSpr.setTexture(*m_playerTex);

    sf::Texture* coinTex = new sf::Texture();
    if (!coinTex->loadFromFile(PATH + "coin.png")) {
        //throw OpenTextureFailed();
    }
    m_coinTex = coinTex;
    m_coinSpr.setTexture(*m_coinTex);

    sf::Texture* obstacleTex = new sf::Texture();
    if (!obstacleTex->loadFromFile(PATH + "Zappers.png")) {
        //throw OpenTextureFailed();
    }
    m_obstacleTex = obstacleTex;
    m_obstacleSpr.setTexture(*m_coinTex);

    sf::Texture titleTex;
    if (!titleTex.loadFromFile(PATH + "Title.png")) {
        //throw OpenTextureFailed();
    }
    m_titleTex = titleTex;
    m_titleSpr.setTexture(m_titleTex);

    for(int index = 0; index < 4; index++){
        if(!m_buttonsTex[index].loadFromFile(PATH + buttons[index])){
            //throw OpenTextureFailed();
        }
        m_buttonsSpr[index].setTexture(m_buttonsTex[index]);
    }

    sf::Texture backgroundTex;
    if (!backgroundTex.loadFromFile(PATH + "Hall.png")) {
        //throw OpenTextureFailed();
    }
    m_backgroundTex = backgroundTex;
    m_backgroundSpr.setTexture(m_backgroundTex);

    sf::Texture backgroundStartTex;
    if (!backgroundStartTex.loadFromFile(PATH + "StartOfHall.png")) {
        //throw OpenTextureFailed();
    }
    m_backgroundStartTex = backgroundStartTex;
    m_backgroundStartSpr.setTexture(m_backgroundStartTex);
}

ResourcesManager &ResourcesManager::instance() {
    static ResourcesManager m_instance;
    return m_instance;
    /*
    try{
        static ResourcesManager m_instance;
        return m_instance;
    } catch (std::exception& e){
        e.what();
    }
    */
}

sf::Sprite ResourcesManager::getTitle() const {
    return m_titleSpr;
}

sf::Sprite ResourcesManager::getPlayerSpr() const {
    return m_playerSpr;
}

sf::Texture* ResourcesManager::getPlayerTex() const{
    return m_playerTex;
}

sf::Sprite ResourcesManager::getButtonsSpr(int index) const {
    return m_buttonsSpr[index];
}

sf::Texture ResourcesManager::getButtonsTex(int index) const {
    return m_buttonsTex[index];
}

sf::Sprite ResourcesManager::getBackground() const{
    return m_backgroundSpr;
}

sf::Texture ResourcesManager::getBackgroundTex() const{
    return m_backgroundTex;
}

sf::Sprite ResourcesManager::getBackgroundStartSpr() const{
    return m_backgroundStartSpr;
}

sf::Texture ResourcesManager::getBackgroundStartTex() const{
    return m_backgroundStartTex;
}

sf::Sprite ResourcesManager::getCoinSpr() const{
    return m_coinSpr;
}

sf::Texture* ResourcesManager::getCoinTex() const{
    return m_coinTex;
}

sf::Texture* ResourcesManager::getObstacle() const{
    return m_obstacleTex;
}