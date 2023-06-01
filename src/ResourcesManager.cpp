
#include "ResourcesManager.h"
#include "Values.h"

ResourcesManager::ResourcesManager() {
    sf::Font font;
    if(!font.loadFromFile(PATH + "Jetpackia.ttf")) {
        throw OpenFontFailed();
    }
    m_font = font;

    sf::Texture* playerTex = new sf::Texture();
    if (!playerTex->loadFromFile(PATH + "Player.png")) {
        throw OpenTextureFailed();
    }
    m_player = playerTex;

    sf::Texture* coinTex = new sf::Texture();
    if (!coinTex->loadFromFile(PATH + "coin.png")) {
        throw OpenTextureFailed();
    }
    m_coin = coinTex;

    sf::Texture* obstacleTex = new sf::Texture();
    if (!obstacleTex->loadFromFile(PATH + "Zappers.png")) {
        throw OpenTextureFailed();
    }
    m_obstacle = obstacleTex;

    sf::Texture* titleTex = new sf::Texture();
    if (!titleTex->loadFromFile(PATH + "Title.png")) {
        throw OpenTextureFailed();
    }
    m_title = titleTex;

    for(int index = 0; index < 4; index++){
        sf::Texture* tempButton = new sf::Texture();
        if(!tempButton->loadFromFile(PATH + buttons[index])){
            throw OpenTextureFailed();
        }
        m_buttons[index] = tempButton;
    }

    sf::Texture* backgroundTex = new sf::Texture();
    if (!backgroundTex->loadFromFile(PATH + "Hall.png")) {
        throw OpenTextureFailed();
    }
    m_background = backgroundTex;

    sf::Texture* backgroundStartTex = new sf::Texture();
    if (!backgroundStartTex->loadFromFile(PATH + "StartOfHall.png")) {
        throw OpenTextureFailed();
    }
    m_firstBackground = backgroundStartTex;

    for (int index = 0; index < 2; index++) {
        sf::Texture* tempDed = new sf::Texture();
        if (!tempDed->loadFromFile(PATH + barryDeath[index])) {
            throw OpenTextureFailed();
        }
        m_barryDeath[index] = tempDed;
    }

    sf::Texture* laiserLine = new sf::Texture();
    if (!laiserLine->loadFromFile(PATH + "beam.png")) {
        throw OpenTextureFailed();
    }
    m_laiserLine = laiserLine;
}

ResourcesManager::~ResourcesManager() {
    delete m_player;
    delete m_firstBackground;
    delete m_background;
    delete m_coin;
    delete m_obstacle;
    delete m_title;
    for(int i = 0; i < 4; i++){
        delete m_buttons[i];
     }
}

ResourcesManager &ResourcesManager::instance() {
    try {
        static ResourcesManager m_instance;
        return m_instance;
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
        throw;
    }
}

sf::Font& ResourcesManager::getFont(){
    return m_font;
}

sf::Texture* ResourcesManager::getTitle() const {
    return m_title;
}

sf::Texture* ResourcesManager::getPlayer() const{
    return m_player;
}

sf::Texture* ResourcesManager::getButtons(int index) const {
    return m_buttons[index];
}

sf::Texture* ResourcesManager::getBackground() const{
    return m_background;
}

sf::Texture* ResourcesManager::getFirstBackground() const{
    return m_firstBackground;
}

sf::Texture* ResourcesManager::getCoin() const{
    return m_coin;
}

sf::Texture* ResourcesManager::getObstacle() const{
    return m_obstacle;
}

sf::Texture* ResourcesManager::getBarryDeath(int index) const {
    return m_barryDeath[index];
}

sf::Texture* ResourcesManager::getLiserLine() const
{
    return m_laiserLine;
}
