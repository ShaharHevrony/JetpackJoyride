#include "GameManager.h"
#include <SFML/Audio/Listener.hpp>

GameManager::GameManager() {
    //Initialize member variables
    m_chosenCharacter = ZERO;
    m_collectedSum = ZERO;
    m_musicVolume = ZERO;
    m_soundVolume = ZERO;

    for (int top = 0; top < TOP_FIVE; top++) { //Initialize top scores to zero
        m_topScore[top] = ZERO;
    }
    readFile(); //Read data from file
}

GameManager& GameManager::instance() {
    try { //Create a static instance of GameManager
        static GameManager m_instance;
        return m_instance;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl; //Print the exception message and re-throw it
        throw;
    }
}

GameManager::~GameManager() {
    writeFile(); //Save data to file
}

void GameManager::readFile() {
    //Check if the file exists, create it if it doesn't
    std::ifstream managerFile;
    std::string filePath = "GameManager.txt";
    if (!std::filesystem::exists(filePath)) {
        throw FileNotExist();
    }
    managerFile.open(filePath, std::fstream::in); //Open the file for reading
    if (!managerFile.is_open()) {
        throw OpenFileFailed(); //Throw an exception if the file cannot be opened
    }
    //Read data from the file
    managerFile >> m_soundVolume;
    managerFile >> m_musicVolume;
    for (int index = 0; index < TOP_FIVE; index++) {
        managerFile >> m_topScore[index];
    }
    managerFile.close(); //Close the file
}

void GameManager::writeFile() {
    //Open the file for writing
    std::ofstream managerFile;
    std::string filePath = "GameManager.txt";
    //If the file exists, clear its contents and create a new empty file
    if (std::filesystem::exists(filePath)) {
        managerFile.open(filePath, std::ios::out | std::ios::trunc);
    } else {
        managerFile.open(filePath); //If the file doesn't exist, create a new file
    }
    if (!managerFile.is_open()) { //Check if the file is open
        throw OpenFileFailed(); //Throw an exception if the file cannot be opened
    }

    managerFile << m_soundVolume << " " << m_musicVolume << "\n"; //Write data to the file
    for (int index = 0; index < TOP_FIVE; index++) {
        managerFile << m_topScore[index] << "\n";
    }
    managerFile.close(); //Close the file
}

void GameManager::sort() {
    //Bubble sort algorithm to sort the top scores in descending order
    for (int i = 0; i < TOP_FIVE - 1; i++) {
        for (int j = 0; j < TOP_FIVE - i - FIRST; j++) {
            if (m_topScore[j] < m_topScore[j + FIRST]) {
                //Swap the elements
                int temp = m_topScore[j];
                m_topScore[j] = m_topScore[j + FIRST];
                m_topScore[j + FIRST] = temp;
            }
        }
    }
}

//Update the potential best score and sort the top scores
void GameManager::checkPotentialBest(int score) {
    if (score > m_topScore[FOUR]) {
        m_topScore[FOUR] = score;
        sort();
    }
}

//Set the top scores array with the provided array values
void GameManager::setTopScore(int* top) {
    for (int index = 0; index < TOP_FIVE; index++) {
        m_topScore[index] = top[index];
    }
}

//Get the top score at the specified index
int GameManager::getTopScore(int index) const {
    return m_topScore[index];
}

//Get the highest top score
int GameManager::getBest() const {
    return m_topScore[ZERO];
}

//Set the sound volume
void GameManager::setSound(int sound) {
    m_soundVolume = sound;
}

//Get the adjusted sound volume based on the global volume level
float GameManager::getSound() const {
    return (sf::Listener::getGlobalVolume() * (m_soundVolume / 100.0f));
}

//Set the music volume
void GameManager::setMusic(int music) {
    m_musicVolume = music;
}

//Get the music volume
int GameManager::getMusic() const {
    return m_musicVolume;
}

//Update the collected sum by adding the provided value
void GameManager::setCollectedSum(int collected) {
    m_collectedSum += collected;
}

//Update the collected sum by subtracting the price of a purchase
void GameManager::setCollectedSumBuy(int price) {
    m_collectedSum -= price;
}

//Get the current collected sum
int GameManager::getCollectedSum() const {
    return m_collectedSum;
}

//Set the chosen character index
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