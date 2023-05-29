#include "Board.h"

Board::Board() {
    try {
        writeObjectFile();
        //readObjectFile();
        readObjectFile(0);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        throw;
    }
}

Board::~Board() {}

void Board::writeObjectFile() {
    std::ofstream writingFile;
    for(int index = 0; index < MAP.size(); index++) {
        std::string filePath = "mapNum"+ std::to_string(index);
        if (std::filesystem::exists(filePath)) {
            //If the file exist then we clear all the file contents and create a new empty file.
            writingFile.open(filePath, std::ios::out | std::ios::trunc);
        } else {
            writingFile.open(filePath);
        }

        if (!writingFile.is_open()) {
            throw OpenFailed();
        }
        writingFile << MAP[index];
        writingFile.close();
    }
}
/*
void Board::readObjectFile() {
    std::ifstream readingFile;
    m_smartMap.resize(MAP.size());
    for(int index = 0; index < MAP.size(); index++) {
        int lineCount = 0;
        std::string filePath = "mapNum"+ std::to_string(index);
        if (!std::filesystem::exists(filePath)) { //Can't open a none existing file
            throw FileNotExist();
        }
        readingFile.open(filePath, std::fstream::in);
        if (!readingFile.is_open()) {             //File doesn't open
            throw OpenFailed();
        }
        m_smartMap.clear();
        std::vector<std::string> tempVector;
        while (!readingFile.eof()) {
            std::string str;
            char my_line[MAP[index].size()][NUM_OF_OBJECTS];
            std::getline(readingFile, str);
            for (int i = 0; i < str.size(); i++) {
                my_line[lineCount][i] = str[i];
            }
            //m_smartMap[index].push_back(my_line[lineCount]);
            tempVector.push_back(my_line[lineCount]);
            lineCount++;
        }
        m_smartMap.push_back(tempVector);
        readingFile.close();
    }
}
*/
std::vector<std::string> Board::getMap(int index) const {
    return m_smartMap[index];
}

void Board::readObjectFile(int index) {
    std::ifstream readingFile;
    std::string filePath = "mapNum" + std::to_string(index);
    if (!std::filesystem::exists(filePath)) { //Can't open a none existing file
        throw FileNotExist();
    }
    readingFile.open(filePath, std::fstream::in);
    if (!readingFile.is_open()) {             //File doesn't open
        throw OpenFailed();
    }
    m_stupidMap.clear();

    while (!readingFile.eof()) {
        std::string str;
        char my_line[NUM_OF_OBJECTS];
        std::getline(readingFile, str);
        for (int i = 0; i < str.size(); i++) {
            my_line[i] = str[i];
        }
        m_stupidMap.push_back(my_line);
    }
    readingFile.close();
}

std::vector<std::string> Board::getMap() const {
    return m_stupidMap;
}

std::vector<sf::Sprite> Board::getBackgrounds() const{
    return m_backgrounds;
}

void Board::setBackgrounds(int size) {
    m_backgrounds.resize(size);
    for (int index = 0; index < size; index++) {
        m_backgrounds[index].setTexture(*ResourcesManager::instance().getBackground());
        m_backgrounds[index].setPosition((index + 1) * ResourcesManager::instance().getBackground()->getSize().x, 0);
    }
}

void Board::setBackgroundPosition(int index, sf::Vector2f position){
    m_backgrounds[index].setPosition(position);
}

sf::Sprite Board::getFirstBackground() const{
    return m_firstBackground;
}

void Board::setFirstBackground() {
    m_firstBackground.setTexture(*ResourcesManager::instance().getFirstBackground());
}

void Board::setFirstBackgroundPosition(sf::Vector2f position) {
    m_firstBackground.setPosition(position);
}

float Board::getWidth() const {
    return ResourcesManager::instance().getBackground()->getSize().x;
}