#include "ResourcesManager.h"
#include "Values.h"

ResourcesManager::ResourcesManager() {
    //--------------------------- Define the game's font ---------------------------
    sf::Font font;
    if(!font.loadFromFile(PATH + "Jetpackia.ttf")) {
        throw OpenFontFailed();
    }
    m_font = font;

    //--------------------------- Define the game's icon ---------------------------
    sf::Image* icon = new sf::Image();
    if (!icon->loadFromFile(PATH + "Icon.png")) {
        throw OpenImageFailed();
    }
    m_icon = icon;

    //---------------------- Define all of the game's textures ---------------------
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

    sf::Texture* beam = new sf::Texture();
    if (!beam->loadFromFile(PATH + "ZappersBeam.png")) {
        throw OpenTextureFailed();
    }
    m_zappersBeam = beam;

    sf::Texture* gameSettingButton = new sf::Texture();
    if (!gameSettingButton->loadFromFile(PATH + "GameSettingButton.png")) {
        throw OpenTextureFailed();
    }
    m_gameSetting = gameSettingButton;

    sf::Texture* backgroundTex = new sf::Texture();
    if (!backgroundTex->loadFromFile(PATH + "Hall.png")) {
        throw OpenTextureFailed();
    }
    m_gameBackground = backgroundTex;

    sf::Texture* backgroundStartTex = new sf::Texture();
    if (!backgroundStartTex->loadFromFile(PATH + "StartOfHall.png")) {
        throw OpenTextureFailed();
    }
    m_gameFirstBackground = backgroundStartTex;

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

    sf::Texture* settingBackground = new sf::Texture();
    if (!settingBackground->loadFromFile(PATH + "settingsMenu.png")) {
        throw OpenTextureFailed();
    }
    m_settingBackground = settingBackground;

    sf::Texture* quit = new sf::Texture();
    if (!quit->loadFromFile(PATH + "quit.png")) {
        throw OpenTextureFailed();
    }
    m_quit = quit;

    //------------------- Define all of the game's arrays texture ------------------
    for(int index = 0; index < buttons.size(); index++){
        sf::Texture* tempButton = new sf::Texture();
        if(!tempButton->loadFromFile(PATH + buttons[index])){
            throw OpenTextureFailed();
        }
        m_buttons[index] = tempButton;
    }

    for(int index = 0; index < berrysDeath.size(); index++) {
        sf::Texture* tempDeath = new sf::Texture();
        if (!tempDeath->loadFromFile(PATH + berrysDeath[index])) {
            throw OpenTextureFailed();
        }
        m_barryDeath[index] = tempDeath;
    }

    for (int index = 0; index < missile.size(); index++) {
        sf::Texture* tempMissile = new sf::Texture();
        if (!tempMissile->loadFromFile(PATH + missile[index])) {
            throw OpenTextureFailed();
        }
        m_missile[index] = tempMissile;
    }

    for (int index = 0; index < superPower.size() ; index++) {
        sf::Texture* tempSuper = new sf::Texture();
        if (!tempSuper->loadFromFile(PATH + superPower[index])) {
            throw OpenTextureFailed();
        }
        m_superPower[index] = tempSuper;
    }

    //----------------------- Define all of the game's audios ----------------------
    sf::SoundBuffer soundCoin;
    if (!soundCoin.loadFromFile(PATH + "Coin.wav")) {
        throw OpenAudioFailed();
    }
    m_soundCoin = soundCoin;

    sf::SoundBuffer soundZapper;
    if (!soundZapper.loadFromFile(PATH + "ZapperSound.wav")) {
        throw OpenAudioFailed();
    }
    m_soundZapper = soundZapper;

    sf::SoundBuffer soundMissileLaunch;
    if (!soundMissileLaunch.loadFromFile(PATH + "missileLaunch.wav")) {
        throw OpenAudioFailed();
    }
    m_soundMissileSound = soundMissileLaunch;

    sf::SoundBuffer soundMissileAlarm;
    if (!soundMissileAlarm.loadFromFile(PATH + "MissileAlarm.wav")) {
        throw OpenAudioFailed();
    }
    m_soundMissileAlarm = soundMissileAlarm;

    sf::SoundBuffer soundMissileHit;
    if (!soundMissileHit.loadFromFile(PATH + "hitSound.wav")) {
        throw OpenAudioFailed();
    }
    m_soundMissileHit = soundMissileHit;
}

ResourcesManager::~ResourcesManager() {
    delete m_icon;
    delete m_gameMenu;
    delete m_title;
    delete m_player;
    delete m_coin;
    delete m_upperZappers;
    delete m_lowerZapper;
    delete m_zappersBeam;
    delete m_gameSetting;
    delete m_gameBackground;
    delete m_gameFirstBackground;
    delete m_flame;
    delete m_piggy;
    delete m_glitter;
    delete m_scientist;
    delete m_settingBackground;
    delete m_quit;

    for(int i = 0; i < buttons.size(); i++){
        delete m_buttons[i];
    }
    for(int i = 0; i < berrysDeath.size(); i++){
        delete m_barryDeath[i];
    }
    for(int i = 0; i < missile.size(); i++){
        delete m_missile[i];
    }
    for(int i = 0; i < superPower.size(); i++){
        delete m_superPower[i];
    }
}

ResourcesManager& ResourcesManager::instance() {
    try {
        static ResourcesManager m_instance;
        return m_instance;
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
        throw;
    }
}

//------------------------------ Get the game's font -------------------------------
sf::Font& ResourcesManager::getFont() {
    return m_font;
}

//------------------------------ Get the game's icon -------------------------------
sf::Image* ResourcesManager::getIcon() const {
    return m_icon;
}

//------------------------- Get all of the game's textures -------------------------
sf::Texture* ResourcesManager::getGameMenu() const {
    return m_gameMenu;
}

sf::Texture* ResourcesManager::getTitle() const {
    return m_title;
}

sf::Texture* ResourcesManager::getPlayer() const {
    return m_player;
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

sf::Texture* ResourcesManager::getZappersBeam() const {
    return m_zappersBeam;
}

sf::Texture* ResourcesManager::getGameSetting() const {
    return m_gameSetting;
}

sf::Texture* ResourcesManager::getGameBackground() const {
    return m_gameBackground;
}

sf::Texture* ResourcesManager::getFirstBackground() const {
    return m_gameFirstBackground;
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

sf::Texture* ResourcesManager::getSettingBackGround() const {
    return m_settingBackground;
}

sf::Texture* ResourcesManager::getQuitKey() const {
    return m_quit;
}

//---------------------- Get all of the game's arrays texture ----------------------
sf::Texture* ResourcesManager::getButtons(int index) const {
    return m_buttons[index];
}

sf::Texture* ResourcesManager::getBarryDeath(int index) const {
    return m_barryDeath[index];
}

sf::Texture* ResourcesManager::getMissile(int index) const {
    return m_missile[index];
}

sf::Texture* ResourcesManager::getSuperPower(int index) const {
    return m_superPower[index];
}

//-------------------------- Get all of the game's audios --------------------------
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

sf::SoundBuffer& ResourcesManager::getSoundMissileHit() {
    return m_soundMissileHit;
}