
#include "ResourcesManager.h"
#include "Values.h"

ResourcesManager::ResourcesManager() {
    //--------------------------- Define the game's font ---------------------------
    sf::Font font;
    if (!font.loadFromFile(PATH + "Jetpackia.ttf")) {
        throw OpenFontFailed();
    }
    m_font = font;

    //--------------------------- Define the game's icon ---------------------------
    if (!m_icon.loadFromFile(PATH + "Icon.png")) {
        throw OpenImageFailed();
    }

    //---------------------- Define all of the game's textures ---------------------
    if (!m_gameMenu.loadFromFile(PATH + "GameMenu.png")) {
        throw OpenTextureFailed();
    }

    if (!m_title.loadFromFile(PATH + "Title.png")) {
        throw OpenTextureFailed();
    }

    if (!m_coin.loadFromFile(PATH + "Coin.png")) {
        throw OpenTextureFailed();
    }

    if (!m_laser.loadFromFile(PATH + "Laser.png")) {
        throw OpenTextureFailed();
    }

    if (!m_lasersBeam.loadFromFile(PATH + "LasersBeam.png")) {
        throw OpenTextureFailed();
    }

    if (!m_gameSetting.loadFromFile(PATH + "GameSettingButton.png")) {
        throw OpenTextureFailed();
    }

    if (!m_gameBackground.loadFromFile(PATH + "Hall.png")) {
        throw OpenTextureFailed();
    }

    if (!m_gameFirstBackground.loadFromFile(PATH + "StartOfHall.png")) {
        throw OpenTextureFailed();
    }

    if (!m_flame.loadFromFile(PATH + "Exhaust.png")) {
        throw OpenTextureFailed();
    }

    if (!m_piggy.loadFromFile(PATH + "Piggy.png")) {
        throw OpenTextureFailed();
    }

    if (!m_glitter.loadFromFile(PATH + "Glitter.png")) {
        throw OpenTextureFailed();
    }

    if (!m_scientist.loadFromFile(PATH + "Scientist.png")) {
        throw OpenTextureFailed();
    }

    if (!m_settingBackground.loadFromFile(PATH + "settingsMenu.png")) {
        throw OpenTextureFailed();
    }

    if (!m_quit.loadFromFile(PATH + "quit.png")) {
        throw OpenTextureFailed();
    }

    if (!m_lights.loadFromFile(PATH + "Lights.png")) {
        throw OpenTextureFailed();
    }

    if (!m_arrow.loadFromFile(PATH + "Arrow.png")) {
        throw OpenTextureFailed();
    }

    if (!m_buy.loadFromFile(PATH + "Buy.png")) {
        throw OpenTextureFailed();
    }

    if (!m_equip.loadFromFile(PATH + "Equip.png")) {
        throw OpenTextureFailed();
    }
    //------------------- Define all of the game's arrays texture ------------------
    for (int type = 0; type < playerStates.size(); type++) {
        for (int state = 0; state < playerStates[type].size(); state++) {
            std::string filePath = PATH + playerStates[type][state];
            if (!m_playerStates[type][state].loadFromFile(filePath)) {
                throw OpenTextureFailed();
            }
        }
    }

    for (int index = 0; index < buttons.size(); index++) {
        if (!m_buttons[index].loadFromFile(PATH + buttons[index])) {
            throw OpenTextureFailed();
        }
    }

    for (int index = 0; index < missile.size(); index++) {
        if (!m_missile[index].loadFromFile(PATH + missile[index])) {
            throw OpenTextureFailed();
        }
    }

    for (int index = 0; index < superPower.size(); index++) {
        if (!m_superPower[index].loadFromFile(PATH + superPower[index])) {
            throw OpenTextureFailed();
        }
    }

    for (int index = 0; index < playersAvatar.size(); index++) {
        if (!m_playerAvatar[index].loadFromFile(PATH + playersAvatar[index])) {
            throw OpenTextureFailed();
        }
    }

    for (int index = 0; index < help.size(); index++) {
        if (!m_help[index].loadFromFile(PATH + help[index])) {
            throw OpenTextureFailed();
        }
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

    if (!m_soundMissileSound.loadFromFile(PATH + "missileLaunch.wav")) {
        throw OpenAudioFailed();
    }

    if (!m_soundMissileAlarm.loadFromFile(PATH + "MissileAlarm.wav")) {
        throw OpenAudioFailed();
    }

    if (!m_soundMissileHit.loadFromFile(PATH + "hitSound.wav")) {
        throw OpenAudioFailed();
    }

    if (!m_soundGetPower.loadFromFile(PATH + "getPowerSound.wav")) {
        throw OpenAudioFailed();
    }

    for (int index = 0; index < settingsButtons.size(); index++) {
        if (!m_gameSettingButtons[index].loadFromFile(PATH + settingsButtons[index])) {
            throw OpenTextureFailed();
        }
    }
}

ResourcesManager::~ResourcesManager() {}

ResourcesManager& ResourcesManager::instance() {
    try {
        static ResourcesManager m_instance;
        return m_instance;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        throw;
    }
}

//------------------------------ Get the game's font -------------------------------
sf::Font& ResourcesManager::getFont() {
    return m_font;
}

//------------------------------ Get the game's icon -------------------------------
sf::Image* ResourcesManager::getIcon() {
    return &m_icon;
}

//------------------------- Get all of the game's textures -------------------------
sf::Texture* ResourcesManager::getGameMenu() {
    return &m_gameMenu;
}

sf::Texture* ResourcesManager::getTitle() {
    return &m_title;
}

sf::Texture* ResourcesManager::getCoin() {
    return &m_coin;
}

sf::Texture* ResourcesManager::getLaser() {
    return &m_laser;
}

sf::Texture* ResourcesManager::getLasersBeam() {
    return &m_lasersBeam;
}

sf::Texture* ResourcesManager::getGameSetting() {
    return &m_gameSetting;
}

sf::Texture* ResourcesManager::getGameBackground() {
    return &m_gameBackground;
}

sf::Texture* ResourcesManager::getFirstBackground() {
    return &m_gameFirstBackground;
}

sf::Texture* ResourcesManager::getFlame() {
    return &m_flame;
}

sf::Texture* ResourcesManager::getPiggy() {
    return &m_piggy;
}

sf::Texture* ResourcesManager::getGlitter() {
    return &m_glitter;
}

sf::Texture* ResourcesManager::getScientist() {
    return &m_scientist;
}

sf::Texture* ResourcesManager::getSettingBackGround() {
    return &m_settingBackground;
}

sf::Texture* ResourcesManager::getQuitKey() {
    return &m_quit;
}

sf::Texture* ResourcesManager::getArrow() {
    return &m_arrow;
}

sf::Texture* ResourcesManager::getBuy() {
    return &m_buy;
}

sf::Texture* ResourcesManager::getEquip() {
    return &m_equip;
}

sf::Texture* ResourcesManager::getSettingButtons(int index) {
    return &m_gameSettingButtons[index];
}

//---------------------- Get all of the game's arrays texture ----------------------
sf::Texture* ResourcesManager::getPlayerStates(int type, int state) {
    return &m_playerStates[type][state];
}

sf::Texture* ResourcesManager::getButtons(int index) {
    return &m_buttons[index];
}

sf::Texture* ResourcesManager::getMissile(int index) {
    return &m_missile[index];
}

sf::Texture* ResourcesManager::getSuperPower(int index) {
    return &m_superPower[index];
}

sf::Texture* ResourcesManager::getHelp(int index) {
    return &m_help[index];
}

sf::Texture* ResourcesManager::getLights() {
    return &m_lights;
}

sf::Texture* ResourcesManager::getAvatar(int index) {
    return &m_playerAvatar[index];
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

sf::SoundBuffer& ResourcesManager::getSoundPowerBox() {
    return m_soundGetPower;
}