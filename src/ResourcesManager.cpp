
#include "ResourcesManager.h"
#include "Values.h"

ResourcesManager::ResourcesManager() {
    sf::Font font;
    if(!font.loadFromFile(PATH + "Jetpackia.ttf")) {
        throw OpenFontFailed();
    }
    m_font = font;

    sf::Texture* gameMenu = new sf::Texture();
    if (!gameMenu->loadFromFile(PATH + "GameMenu.png")) {
        throw OpenTextureFailed();
    }
    m_gameMenu = gameMenu;

    sf::Texture* titleTex = new sf::Texture();
    if (!titleTex->loadFromFile(PATH + "Title.png")) {
        throw OpenTextureFailed();
    }
    m_title = titleTex;

    sf::Texture* playerTex = new sf::Texture();
    if (!playerTex->loadFromFile(PATH + "Player.png")) {
        throw OpenTextureFailed();
    }
    m_player = playerTex;

    sf::Texture* coinTex = new sf::Texture();
    if (!coinTex->loadFromFile(PATH + "Coin.png")) {
        throw OpenTextureFailed();
    }
    m_coin = coinTex;

    sf::Texture* upperZappers = new sf::Texture();
    if (!upperZappers->loadFromFile(PATH + "UpperZappers.png")) {
        throw OpenTextureFailed();
    }
    m_upperZappers = upperZappers;

    sf::Texture* lowerZappers = new sf::Texture();
    if (!lowerZappers->loadFromFile(PATH + "LowerZappers.png")) {
        throw OpenTextureFailed();
    }
    m_lowerZapper = lowerZappers;


    for(int index = 0; index < 8; index++){
        sf::Texture* tempButton = new sf::Texture();
        if(!tempButton->loadFromFile(PATH + buttons[index])){
            throw OpenTextureFailed();
        }
        m_buttons[index] = tempButton;
    }

    sf::Texture* gameSettingButton = new sf::Texture();
    if (!gameSettingButton->loadFromFile(PATH + "GameSettingButton.png")) {
        throw OpenTextureFailed();
    }
    m_gameSetting = gameSettingButton;

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

    sf::Texture* berryHit = new sf::Texture();
    if (!berryHit->loadFromFile(PATH + "BerryHit.png")) {
        throw OpenTextureFailed();
    }
    m_barryDeath[0] = berryHit;

    sf::Texture* berryDead = new sf::Texture();
    if (!berryDead->loadFromFile(PATH + "BerryDead.png")) {
        throw OpenTextureFailed();
    }
    m_barryDeath[1] = berryDead;

    sf::Texture* beam = new sf::Texture();
    if (!beam->loadFromFile(PATH + "ZappersBeam.png")) {
        throw OpenTextureFailed();
    }
    m_zappersBeam = beam;

    for (int index = 0; index < 3; index++) {
        sf::Texture* tempMissile = new sf::Texture();
        if (!tempMissile->loadFromFile(PATH + missile[index])) {
            throw OpenTextureFailed();
        }
        m_missile[index] = tempMissile;
    }

    sf::Texture* flame = new sf::Texture();
    if (!flame->loadFromFile(PATH + "Exhaust.png")) {
        throw OpenTextureFailed();
    }
    m_flame = flame;

    sf::Texture* piggy = new sf::Texture();
    if (!piggy->loadFromFile(PATH + "Piggy.png")) {
        throw OpenTextureFailed();
    }
    m_piggy = piggy;

    sf::Texture* glitter = new sf::Texture();
    if (!glitter->loadFromFile(PATH + "Glitter.png")) {
        throw OpenTextureFailed();
    }
    m_glitter = glitter;

    sf::Texture* scientist = new sf::Texture();
    if (!scientist->loadFromFile(PATH + "Scientist.png")) {
        throw OpenTextureFailed();
    }
    m_scientist = scientist;

    for (int index = 0; index < 3; index++) {
        sf::Texture* tempSuper = new sf::Texture();
        if (!tempSuper->loadFromFile(PATH + superPower[index])) {
            throw OpenTextureFailed();
        }
        m_superPower[index] = tempSuper;
    }

    //load pacman death sound
    sf::SoundBuffer soundCoin;
    if (!soundCoin.loadFromFile(PATH + "Coin.wav")) {
        // Error loading sound file
    }
    m_soundCoin = soundCoin;

    //load pacman death sound
    sf::SoundBuffer soundZapper;
    if (!soundZapper.loadFromFile(PATH + "ZapperSound.wav")) {
        // Error loading sound file
    }
    m_soundZapper = soundZapper;

    //load pacman death sound
    sf::SoundBuffer soundMissileLaunch;
    if (!soundMissileLaunch.loadFromFile(PATH + "missileLaunch.wav")) {
        // Error loading sound file
    }
    m_soundMissileSound = soundMissileLaunch;

    //load pacman death sound
    sf::SoundBuffer soundMissileAlarm;
    if (!soundMissileAlarm.loadFromFile(PATH + "MissileAlarm.wav")) {
        // Error loading sound file
    }
    m_soundMissileAlarm = soundMissileAlarm;
}

ResourcesManager::~ResourcesManager() {
    delete m_player;
    delete m_firstBackground;
    delete m_background;
    delete m_coin;
    delete m_upperZappers;
    delete m_lowerZapper;
    delete m_gameMenu;
    delete m_zappersBeam;
    delete m_piggy;
    delete m_gameSetting;
    delete m_flame;
    delete m_glitter;

    for(int i = 0; i < 8; i++){
        delete m_buttons[i];
    }
    for(int i = 0; i < 2; i++){
        delete m_barryDeath[i];
    }
    for(int i = 0; i < 3; i++){
        delete m_missile[i];
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

sf::Font& ResourcesManager::getFont() {
    return m_font;
}

sf::Texture* ResourcesManager::getGameMenu() const {
    return m_gameMenu;
}

sf::Texture* ResourcesManager::getTitle() const {
    return m_title;
}

sf::Texture* ResourcesManager::getPlayer() const {
    return m_player;
}

sf::Texture* ResourcesManager::getButtons(int index) const {
    return m_buttons[index];
}

sf::Texture* ResourcesManager::getGameSetting() const {
    return m_gameSetting;
}

sf::Texture* ResourcesManager::getBackground() const {
    return m_background;
}

sf::Texture* ResourcesManager::getFirstBackground() const {
    return m_firstBackground;
}

sf::Texture* ResourcesManager::getCoin() const {
    return m_coin;
}

sf::Texture* ResourcesManager::getUpperZappers() const{
    return m_upperZappers;
}

sf::Texture* ResourcesManager::getLowerZappers() const{
    return m_lowerZapper;
}

sf::Texture* ResourcesManager::getBarryDeath(int index) const {
    return m_barryDeath[index];
}

sf::Texture* ResourcesManager::getZappersBeam() const {
    return m_zappersBeam;
}

sf::Texture* ResourcesManager::getMissile(int index) const {
    return m_missile[index];
}

sf::Texture* ResourcesManager::getFlame() const {
    return m_flame;
}

sf::Texture* ResourcesManager::getPiggy() const {
    return m_piggy;
}

sf::Texture* ResourcesManager::getGlitter() const {
    return m_glitter;
}

sf::Texture* ResourcesManager::getScientist() const{
    return m_scientist;
}

sf::Texture* ResourcesManager::getSuperPower(int index) const {
    return m_superPower[index];
}

sf::SoundBuffer& ResourcesManager::getSoundCoin() {
    return m_soundCoin;
}

sf::SoundBuffer& ResourcesManager::getSoundZapper() {
    return m_soundZapper;
}

sf::SoundBuffer& ResourcesManager::getSoundMissileLaunch() {
    return m_soundMissileSound;
}

sf::SoundBuffer& ResourcesManager::getSoundMissileAlarm() {
    return m_soundMissileAlarm;
}