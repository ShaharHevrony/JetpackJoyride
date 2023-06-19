#include "GameManager.h"
#include <SFML/Audio/Listener.hpp>

GameManager::GameManager() {
    m_chosenCharacter = 0;
    m_collectedSum = 0;
    m_musicVolume = 0;
    m_soundVolume = 0;
    for(int top = 0; top < TOP_FIVE; top++) {
        m_topScore[top] = 0;
    }
    readFile();
}

GameManager& GameManager::instance() {
    try {
        static GameManager m_instance;
        return m_instance;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        throw;
    }
}

GameManager::~GameManager() {
    writeFile();
}

void GameManager::readFile() {
    std::ifstream managerFile;
    std::string filePath = "GameManager";
    if (!std::filesystem::exists(filePath)) { //Can't open a none existing file
        writeFile();
    }
    managerFile.open(filePath, std::fstream::in);
    if (!managerFile.is_open()) {             //File doesn't open
        throw OpenFileFailed();
    }
    managerFile >> m_soundVolume;
    managerFile >> m_musicVolume;
    for (int index = 0; index < TOP_FIVE; index++) {
        managerFile >> m_topScore[index];
    }
    managerFile.close();
}

void GameManager::writeFile() {
    std::ofstream managerFile;
    std::string filePath = "GameManager";
    if (std::filesystem::exists(filePath)) {
        //If the file exist then we clear all the file contents and create a new empty file.
        managerFile.open(filePath, std::ios::out | std::ios::trunc);
    } else {
        managerFile.open(filePath);
    }
    if (!managerFile.is_open()) {
        throw OpenFileFailed();
    }
    managerFile << m_soundVolume << " " << m_musicVolume << "\n";
    for(int index = 0; index < TOP_FIVE; index++) {
        managerFile << m_topScore[index] << "\n";
    }
    managerFile.close();
}

void GameManager::sort() {
    for (int i = 0; i < TOP_FIVE - 1; i++) {
        for (int j = 0; j < TOP_FIVE - i - 1; j++) {
            if (m_topScore[j] < m_topScore[j + 1]) {
                //Swap the elements
                int temp = m_topScore[j];
                m_topScore[j] = m_topScore[j + 1];
                m_topScore[j + 1] = temp;
            }
        }
    }
}

void GameManager::checkPotentialBest(int score) {
    if (score > m_topScore[4]){
        m_topScore[4] = score;
        sort();
    }
}

void GameManager::setTopScore(int* top) {
    for(int index = 0; index < TOP_FIVE; index++) {
        m_topScore[index] = top[index];
    }
}

int GameManager::getTopScore(int index) const {
    return m_topScore[index];
}

void GameManager::setSound(int sound) {
    m_soundVolume = sound;
}

float GameManager::getSound() const {

    return (sf::Listener::getGlobalVolume() * (m_soundVolume / 100.0f));
}

void GameManager::setMusic(int music) {
    m_musicVolume = music;
}

int GameManager::getMusic() const {
    return m_musicVolume;
}

void GameManager::setCollectedSum(int collected) {
    m_collectedSum += collected;
}

void GameManager::setcollctedSumBuy(int price)
{
    m_collectedSum -= price;
}

int GameManager::getCollectedSum() const {
    return m_collectedSum;
}

void GameManager::setCharacter(int character) {
    m_chosenCharacter = character;
}

int GameManager::getCharacter() const {
    return m_chosenCharacter;
}

bool GameManager::getOwned(int index) const {
    return m_ownedGear[index];
}

void GameManager::setOwned(int index) {
    m_ownedGear[index] = true;
}