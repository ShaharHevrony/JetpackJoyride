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

void Board::draw(sf::RenderWindow* window) {
    for (auto &background : m_backgrounds) {
        window->draw(background);
    }
    window->draw(m_firstBackground);
    for(auto &nonCollObj : m_nonCollObj) {
        nonCollObj->draw(window);
    }
}

void Board::moveBackgrounds() {
    if(m_speedIncrease >= CHANGE_INTERVAL) {
        m_speed += ACCELERATION;
        m_speedIncrease -= CHANGE_INTERVAL;
    }
    m_time = m_loopClock.getElapsedTime().asSeconds();
    m_speedIncrease += m_time;
    m_loopClock.restart();

    m_firstBackground.move(DIRECTION * m_time * m_speed);
    if (m_firstBackground.getPosition().x > -(WINDOW_WIDTH)) {
        //Move the second background sprite based on the first one
        sf::Vector2f position = m_backgrounds[1].getPosition();
        position.x = m_firstBackground.getPosition().x + m_firstBackground.getGlobalBounds().width;
        m_backgrounds[1].setPosition(position);
        //Move the third background sprite based on the second one
        position = m_backgrounds[2].getPosition();
        position.x = m_backgrounds[1].getPosition().x + m_backgrounds[1].getGlobalBounds().width;
        m_backgrounds[2].setPosition(position);
    }

    for (int index = 0; index < 3; index++) {
        m_backgrounds[index].move(DIRECTION * m_time * m_speed);
        if (m_backgrounds[index].getPosition().x + m_backgrounds[index].getGlobalBounds().width < 0) {
            sf::Vector2f position = m_backgrounds[(index + 2) % BACKGROUND].getPosition();
            position.x += m_backgrounds[(index + 2) % BACKGROUND].getGlobalBounds().width - 10;
            m_backgrounds[index].setPosition(position);
        }
    }

    for(auto &nonCollObj : m_nonCollObj) {
        nonCollObj->animate();
        nonCollObj->move(m_time * m_speed);
        if (nonCollObj->getObject().getPosition().x <= LAST_POSITION) {
            nonCollObj->setPosition();
        }
    }
}

void Board::animate() {
    for(auto &nonCollObj : m_nonCollObj) {
        nonCollObj->animate();
    }
}

std::vector<std::string> Board::getMap() const {
    auto ptr = m_allMaps.begin();
    std::advance(ptr, m_random);
    return *ptr;
}

void Board::setBackgrounds(int size) {
    m_firstBackground.setTexture(*ResourcesManager::instance().getFirstBackground());
    m_firstBackground.setScale(WINDOW_HEIGHT/m_firstBackground.getTexture()->getSize().y, WINDOW_HEIGHT/m_firstBackground.getTexture()->getSize().y);

    sf::Sprite tempBackground;
    float mapLength = 0.f;
    for (int index = 0; index < size; index++) {
        tempBackground.setTexture(*ResourcesManager::instance().getGameBackground());
        tempBackground.setPosition(index * ResourcesManager::instance().getGameBackground()->getSize().x - index, 0);
        tempBackground.setScale(WINDOW_HEIGHT/tempBackground.getTexture()->getSize().y, WINDOW_HEIGHT/tempBackground.getTexture()->getSize().y);
        m_backgrounds.push_back(tempBackground);

        mapLength += tempBackground.getPosition().x;
    }
    int space = mapLength / WIDTH_GAP;
    int centerMod = 10;
    int randSci;
    for (int index = 0; index <= space; index++) {
        randSci = 1 + rand() % centerMod;
        sf::Vector2f lightPosition = sf::Vector2f(WINDOW_WIDTH + index * WIDTH_CENTER * tempBackground.getScale().y, GAME_SETTING_Y);
        m_nonCollObj.push_back(std::make_unique<Light>(ResourcesManager::instance().getLights(), lightPosition));
        sf::Vector2f scientistPosition = sf::Vector2f(WINDOW_WIDTH + randSci * randSci * tempBackground.getScale().y, WINDOW_HEIGHT/1.28);
        m_nonCollObj.push_back(std::make_unique<Scientist>(ResourcesManager::instance().getScientist(), scientistPosition));
    }
}

void Board::randMap() {
    srand(time(nullptr));
    m_random = rand() % MAP.size();
    if (m_mapCount.size() != MAP.size()) {
        while (m_mapCount.contains(m_random)) {
            m_random = rand() % MAP.size();
        }
        m_mapCount.insert(m_random);
    } else {
        m_mapCount.clear();
    }
}

float Board::getTime() const {
    return m_time;
}

float Board::getMovement() const {
    return m_time * m_speed;
}

void Board::setClock() {
    m_loopClock.restart();
}