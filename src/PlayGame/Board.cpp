#include "Board.h"

Board::Board() {
    m_allMaps.clear();
    try {
        writeObjectFile();
        for(int index = 0; index < MAP.size(); index++){
            readObjectFile(index);
            m_allMaps.insert(m_map);
        }
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
            throw OpenFileFailed();
        }
        writingFile << MAP[index];
        writingFile.close();
    }
}

void Board::readObjectFile(int index) {
    m_map.clear();
    std::ifstream readingFile;
    std::string filePath = "mapNum" + std::to_string(index);
    if (!std::filesystem::exists(filePath)) { //Can't open a none existing file
        throw FileNotExist();
    }
    readingFile.open(filePath, std::fstream::in);
    if (!readingFile.is_open()) {             //File doesn't open
        throw OpenFileFailed();
    }

    while (!readingFile.eof()) {
        std::string str;
        char my_line[NUM_OF_OBJECTS];
        std::getline(readingFile, str);
        for (int i = 0; i < str.size(); i++) {
            my_line[i] = str[i];
        }
        m_map.push_back(my_line);
    }
    readingFile.close();
}

void Board::moveBackgrounds(float time) {
    sf::Vector2f direction(-1,0);
    m_firstBackground.move(direction*time);
    for (int index = 0; index < 3; index++) {
        m_backgrounds[index].move(direction * time);
        if (m_backgrounds[index].getPosition().x + m_backgrounds[index].getGlobalBounds().width < 0) {
            sf::Vector2f position = m_backgrounds[(index + 2) % 3].getPosition();
            position.x += m_backgrounds[(index + 2) % 3].getGlobalBounds().width;
            m_backgrounds[index].setPosition(position);
        }
    }
}

std::vector<std::string> Board::getMap(int index) const {
    auto ptr = m_allMaps.begin();
    std::advance(ptr, index);
    return *ptr;
}

std::vector<sf::Sprite> Board::getBackgrounds() const{
    return m_backgrounds;
}

void Board::setBackgrounds(int size) {
    m_backgrounds.resize(size);
    for (int index = 0; index < size; index++) {
        m_backgrounds[index].setTexture(*ResourcesManager::instance().getBackground());
        m_backgrounds[index].setPosition(index * ResourcesManager::instance().getBackground()->getSize().x - index, 0);
    }
}

void Board::setBorderPosition(int index){
    m_backgrounds[index].setPosition((BACKGROUND - 1) * ResourcesManager::instance().getBackground()->getSize().x - BACKGROUND, 0);
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