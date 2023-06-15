//#include "ResourcesManager.h"
//#include "Values.h"
//
//ResourcesManager::ResourcesManager() {
//    //--------------------------- Define the game's font ---------------------------
//    sf::Font font;
//    if(!font.loadFromFile(PATH + "Jetpackia.ttf")) {
//        throw OpenFontFailed();
//    }
//    m_font = font;
//
//    //--------------------------- Define the game's icon ---------------------------
//    sf::Image* icon = new sf::Image();
//    if (!icon->loadFromFile(PATH + "Icon.png")) {
//        throw OpenImageFailed();
//    }
//    m_icon = icon;
//
//    //---------------------- Define all of the game's textures ---------------------
//    sf::Texture* gameMenu = new sf::Texture();
//    if (!gameMenu->loadFromFile(PATH + "GameMenu.png")) {
//        throw OpenTextureFailed();
//    }
//    m_gameMenu = gameMenu;
//
//    sf::Texture* titleTex = new sf::Texture();
//    if (!titleTex->loadFromFile(PATH + "Title.png")) {
//        throw OpenTextureFailed();
//    }
//    m_title = titleTex;
//
//    sf::Texture* playerTex = new sf::Texture();
//    if (!playerTex->loadFromFile(PATH + "BerryWalking.png")) {
//        throw OpenTextureFailed();
//    }
//    m_player = playerTex;
//
//    sf::Texture* coinTex = new sf::Texture();
//    if (!coinTex->loadFromFile(PATH + "Coin.png")) {
//        throw OpenTextureFailed();
//    }
//    m_coin = coinTex;
//
//    sf::Texture* upperZappers = new sf::Texture();
//    if (!upperZappers->loadFromFile(PATH + "UpperZappers.png")) {
//        throw OpenTextureFailed();
//    }
//    m_upperZappers = upperZappers;
//
//    sf::Texture* lowerZappers = new sf::Texture();
//    if (!lowerZappers->loadFromFile(PATH + "LowerZappers.png")) {
//        throw OpenTextureFailed();
//    }
//    m_lowerZapper = lowerZappers;
//
//    sf::Texture* beam = new sf::Texture();
//    if (!beam->loadFromFile(PATH + "ZappersBeam.png")) {
//        throw OpenTextureFailed();
//    }
//    m_zappersBeam = beam;
//
//    sf::Texture* gameSettingButton = new sf::Texture();
//    if (!gameSettingButton->loadFromFile(PATH + "GameSettingButton.png")) {
//        throw OpenTextureFailed();
//    }
//    m_gameSetting = gameSettingButton;
//
//    sf::Texture* backgroundTex = new sf::Texture();
//    if (!backgroundTex->loadFromFile(PATH + "Hall.png")) {
//        throw OpenTextureFailed();
//    }
//    m_gameBackground = backgroundTex;
//
//    sf::Texture* backgroundStartTex = new sf::Texture();
//    if (!backgroundStartTex->loadFromFile(PATH + "StartOfHall.png")) {
//        throw OpenTextureFailed();
//    }
//    m_gameFirstBackground = backgroundStartTex;
//
//    sf::Texture* flame = new sf::Texture();
//    if (!flame->loadFromFile(PATH + "Exhaust.png")) {
//        throw OpenTextureFailed();
//    }
//    m_flame = flame;
//
//    sf::Texture* piggy = new sf::Texture();
//    if (!piggy->loadFromFile(PATH + "Piggy.png")) {
//        throw OpenTextureFailed();
//    }
//    m_piggy = piggy;
//
//    sf::Texture* glitter = new sf::Texture();
//    if (!glitter->loadFromFile(PATH + "Glitter.png")) {
//        throw OpenTextureFailed();
//    }
//    m_glitter = glitter;
//
//    sf::Texture* scientist = new sf::Texture();
//    if (!scientist->loadFromFile(PATH + "Scientist.png")) {
//        throw OpenTextureFailed();
//    }
//    m_scientist = scientist;
//
//    sf::Texture* settingBackground = new sf::Texture();
//    if (!settingBackground->loadFromFile(PATH + "settingsMenu.png")) {
//        throw OpenTextureFailed();
//    }
//    m_settingBackground = settingBackground;
//
//    sf::Texture* quit = new sf::Texture();
//    if (!quit->loadFromFile(PATH + "quit.png")) {
//        throw OpenTextureFailed();
//    }
//    m_quit = quit;
//
//    sf::Texture* lights = new sf::Texture();
//    if (!lights->loadFromFile(PATH + "Lights.png")) {
//        throw OpenTextureFailed();
//    }
//    m_lights = lights;
//
//    sf::Texture* superPowerRunning = new sf::Texture();
//    if (!superPowerRunning->loadFromFile(PATH + "SuperPowerRunner.png")) {
//        throw OpenTextureFailed();
//    }
//    m_SuperPowerRunner = superPowerRunning;
//
//    sf::Texture* arrow = new sf::Texture();
//    if (!arrow->loadFromFile(PATH + "arrow.png")) {
//        throw OpenTextureFailed();
//    }
//    m_arrow = arrow;
//
//    //------------------- Define all of the game's arrays texture ------------------
//    for(int index = 0; index < buttons.size(); index++){
//        sf::Texture* tempButton = new sf::Texture();
//        if(!tempButton->loadFromFile(PATH + buttons[index])){
//            throw OpenTextureFailed();
//        }
//        m_buttons[index] = tempButton;
//    }
//
//    for(int index = 0; index < berrysDeath.size(); index++) {
//        sf::Texture* tempDeath = new sf::Texture();
//        if (!tempDeath->loadFromFile(PATH + berrysDeath[index])) {
//            throw OpenTextureFailed();
//        }
//        m_barryDeath[index] = tempDeath;
//    }
//
//    for (int index = 0; index < missile.size(); index++) {
//        sf::Texture* tempMissile = new sf::Texture();
//        if (!tempMissile->loadFromFile(PATH + missile[index])) {
//            throw OpenTextureFailed();
//        }
//        m_missile[index] = tempMissile;
//    }
//
//    for (int index = 0; index < superPower.size() ; index++) {
//        sf::Texture* tempSuper = new sf::Texture();
//        if (!tempSuper->loadFromFile(PATH + superPower[index])) {
//            throw OpenTextureFailed();
//        }
//        m_superPower[index] = tempSuper;
//    }
//
//    for (int index = 0; index < playersAvatar.size(); index++) {
//        sf::Texture* tempAvatar = new sf::Texture();
//        if (!tempAvatar->loadFromFile(PATH + playersAvatar[index])) {
//            throw OpenTextureFailed();
//        }
//        m_playerAva[index] = tempAvatar;
//    }
//
//    //----------------------- Define all of the game's audios ----------------------
//    sf::SoundBuffer soundCoin;
//    if (!soundCoin.loadFromFile(PATH + "Coin.wav")) {
//        throw OpenAudioFailed();
//    }
//    m_soundCoin = soundCoin;
//
//    sf::SoundBuffer soundZapper;
//    if (!soundZapper.loadFromFile(PATH + "ZapperSound.wav")) {
//        throw OpenAudioFailed();
//    }
//    m_soundZapper = soundZapper;
//
//    sf::SoundBuffer soundMissileLaunch;
//    if (!soundMissileLaunch.loadFromFile(PATH + "missileLaunch.wav")) {
//        throw OpenAudioFailed();
//    }
//    m_soundMissileSound = soundMissileLaunch;
//
//    sf::SoundBuffer soundMissileAlarm;
//    if (!soundMissileAlarm.loadFromFile(PATH + "MissileAlarm.wav")) {
//        throw OpenAudioFailed();
//    }
//    m_soundMissileAlarm = soundMissileAlarm;
//
//    sf::SoundBuffer soundMissileHit;
//    if (!soundMissileHit.loadFromFile(PATH + "hitSound.wav")) {
//        throw OpenAudioFailed();
//    }
//    m_soundMissileHit = soundMissileHit;
//
//    sf::SoundBuffer soundPowerBox;
//    if (!soundPowerBox.loadFromFile(PATH + "getPowerSound.wav")) {
//        throw OpenAudioFailed();
//    }
//    m_soundGetPower = soundPowerBox;
//}
//
//ResourcesManager::~ResourcesManager() {
//    delete m_icon;
//    delete m_gameMenu;
//    delete m_title;
//    delete m_player;
//    delete m_coin;
//    delete m_upperZappers;
//    delete m_lowerZapper;
//    delete m_zappersBeam;
//    delete m_gameSetting;
//    delete m_gameBackground;
//    delete m_gameFirstBackground;
//    delete m_flame;
//    delete m_piggy;
//    delete m_glitter;
//    delete m_scientist;
//    delete m_settingBackground;
//    delete m_quit;
//
//    for(int i = 0; i < buttons.size(); i++){
//        delete m_buttons[i];
//    }
//    for(int i = 0; i < berrysDeath.size(); i++){
//        delete m_barryDeath[i];
//    }
//    for(int i = 0; i < missile.size(); i++) {
//        delete m_missile[i];
//    }
//    for(int i = 0; i < superPower.size(); i++){
//        delete m_superPower[i];
//    }
//}
//
//ResourcesManager& ResourcesManager::instance() {
//    try {
//        static ResourcesManager m_instance;
//        return m_instance;
//    } catch (std::exception& e){
//        std::cout << e.what() << std::endl;
//        throw;
//    }
//}
//
////------------------------------ Get the game's font -------------------------------
//sf::Font& ResourcesManager::getFont() {
//    return m_font;
//}
//
////------------------------------ Get the game's icon -------------------------------
//sf::Image* ResourcesManager::getIcon() const {
//    return m_icon;
//}
//
////------------------------- Get all of the game's textures -------------------------
//sf::Texture* ResourcesManager::getGameMenu() const {
//    return m_gameMenu;
//}
//
//sf::Texture* ResourcesManager::getTitle() const {
//    return m_title;
//}
//
//sf::Texture* ResourcesManager::getPlayer() const {
//    return m_player;
//}
//
//sf::Texture* ResourcesManager::getCoin() const {
//    return m_coin;
//}
//
//sf::Texture* ResourcesManager::getUpperZappers() const {
//    return m_upperZappers;
//}
//
//sf::Texture* ResourcesManager::getLowerZappers() const {
//    return m_lowerZapper;
//}
//
//sf::Texture* ResourcesManager::getZappersBeam() const {
//    return m_zappersBeam;
//}
//
//sf::Texture* ResourcesManager::getGameSetting() const {
//    return m_gameSetting;
//}
//
//sf::Texture* ResourcesManager::getGameBackground() const {
//    return m_gameBackground;
//}
//
//sf::Texture* ResourcesManager::getFirstBackground() const {
//    return m_gameFirstBackground;
//}
//
//sf::Texture* ResourcesManager::getFlame() const {
//    return m_flame;
//}
//
//sf::Texture* ResourcesManager::getPiggy() const {
//    return m_piggy;
//}
//
//sf::Texture* ResourcesManager::getGlitter() const {
//    return m_glitter;
//}
//
//sf::Texture* ResourcesManager::getScientist() const{
//    return m_scientist;
//}
//
//sf::Texture* ResourcesManager::getSettingBackGround() const {
//    return m_settingBackground;
//}
//
//sf::Texture* ResourcesManager::getQuitKey() const {
//    return m_quit;
//}
//
//sf::Texture* ResourcesManager::getArrow() const {
//    return m_arrow;
//}
////---------------------- Get all of the game's arrays texture ----------------------
//sf::Texture* ResourcesManager::getButtons(int index) const {
//    return m_buttons[index];
//}
//
//sf::Texture* ResourcesManager::getBarryDeath(int index) const {
//    return m_barryDeath[index];
//}
//
//sf::Texture* ResourcesManager::getMissile(int index) const {
//    return m_missile[index];
//}
//
//sf::Texture* ResourcesManager::getSuperPower(int index) const {
//    return m_superPower[index];
//}
//
//sf::Texture* ResourcesManager::getAvatar(int index) const {
//    return m[index];
//}
//
//sf::Texture* ResourcesManager::getLights() const {
//    return m_lights;
//}
//
//sf::Texture* ResourcesManager::getSuperPowerRunner() const {
//    return m_SuperPowerRunner;
//}
//
////-------------------------- Get all of the game's audios --------------------------
//sf::SoundBuffer& ResourcesManager::getSoundCoin() {
//    return m_soundCoin;
//}
//
//sf::SoundBuffer& ResourcesManager::getSoundZapper() {
//    return m_soundZapper;
//}
//
//sf::SoundBuffer& ResourcesManager::getSoundMissileLaunch() {
//    return m_soundMissileSound;
//}
//
//sf::SoundBuffer& ResourcesManager::getSoundMissileAlarm() {
//    return m_soundMissileAlarm;
//}
//
//sf::SoundBuffer& ResourcesManager::getSoundMissileHit() {
//    return m_soundMissileHit;
//}
//
//sf::SoundBuffer& ResourcesManager::getSoundPowerBox() {
//    return m_soundGetPower;
//}
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

    if (!m_player.loadFromFile(PATH + "BerryWalking.png")) {
        throw OpenTextureFailed();
    }

    if (!m_coin.loadFromFile(PATH + "Coin.png")) {
        throw OpenTextureFailed();
    }

    if (!m_upperZappers.loadFromFile(PATH + "UpperZappers.png")) {
        throw OpenTextureFailed();
    }

    if (!m_lowerZapper.loadFromFile(PATH + "LowerZappers.png")) {
        throw OpenTextureFailed();
    }

    if (!m_zappersBeam.loadFromFile(PATH + "ZappersBeam.png")) {
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

    if (!m_SuperPowerRunner.loadFromFile(PATH + "SuperPowerRunner.png")) {
        throw OpenTextureFailed();
    }

    if (!m_arrow.loadFromFile(PATH + "arrow.png")) {
        throw OpenTextureFailed();
    }

    //------------------- Define all of the game's arrays texture ------------------
    for (int index = 0; index < buttons.size(); index++) {
        if (!m_buttons[index].loadFromFile(PATH + buttons[index])) {
            throw OpenTextureFailed();
        }
    }

    for (int index = 0; index < berrysDeath.size(); index++) {
        if (!m_barryDeath[index].loadFromFile(PATH + berrysDeath[index])) {
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
        if (!m_playerAva[index].loadFromFile(PATH + playersAvatar[index])) {
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

sf::Texture* ResourcesManager::getPlayer() {
    return &m_player;
}

sf::Texture* ResourcesManager::getCoin() {
    return &m_coin;
}

sf::Texture* ResourcesManager::getUpperZappers() {
    return &m_upperZappers;
}

sf::Texture* ResourcesManager::getLowerZappers() {
    return &m_lowerZapper;
}

sf::Texture* ResourcesManager::getZappersBeam() {
    return &m_zappersBeam;
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
//---------------------- Get all of the game's arrays texture ----------------------
sf::Texture* ResourcesManager::getButtons(int index) {
    return &m_buttons[index];
}

sf::Texture* ResourcesManager::getBarryDeath(int index) {
    return &m_barryDeath[index];
}

sf::Texture* ResourcesManager::getMissile(int index) {
    return &m_missile[index];
}

sf::Texture* ResourcesManager::getSuperPower(int index) {
    return &m_superPower[index];
}

sf::Texture* ResourcesManager::getLights() {
    return &m_lights;
}

sf::Texture* ResourcesManager::getSuperPowerRunner() {
    return &m_SuperPowerRunner;
}

sf::Texture* ResourcesManager::getAvatar(int index) {
    return &m_playerAva[index];
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