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

void Board::draw(sf::RenderWindow* window, Control& control, int playerType) {
    float changeInterval = 3.0f;
    //Calculate the elapsed time in seconds
    control.Time_t = control.LoopClock_t.getElapsedTime().asSeconds();
    float elapsedTime = control.Time_t;
    if (elapsedTime >= changeInterval) {
        control.Speed_t += 15.f;
    }

    control.LoopClock_t.restart();
    if(playerType == Regular || playerType == SuperPowerTank || playerType == SuperPowerRunner) {
        moveBackgrounds(control.Time_t * control.Speed_t);
    }
    for (int i = 0; i < BACKGROUND; ++i) {
        window->draw(getBackgrounds()[i]);
    }
    window->draw(getFirstBackground());
}

void Board::moveBackgrounds(float time) {
    sf::Vector2f direction(-1,0);
    m_firstBackground.move(direction*time);
    if (m_firstBackground.getPosition().x > -(WINDOW_WIDTH)) {
        // Move the second background sprite based on the first one
        sf::Vector2f position = m_backgrounds[1].getPosition();
        position.x = m_firstBackground.getPosition().x + m_firstBackground.getGlobalBounds().width;
        m_backgrounds[1].setPosition(position);
        // Move the third background sprite based on the second one
        position = m_backgrounds[2].getPosition();
        position.x = m_backgrounds[1].getPosition().x + m_backgrounds[1].getGlobalBounds().width;
        m_backgrounds[2].setPosition(position);
    }
    for (int index = 0; index < 3; index++) {
        m_backgrounds[index].move(direction * time);
        if (m_backgrounds[index].getPosition().x + m_backgrounds[index].getGlobalBounds().width < 0) {
            sf::Vector2f position = m_backgrounds[(index + 2) % BACKGROUND].getPosition();
            position.x += m_backgrounds[(index + 2) % BACKGROUND].getGlobalBounds().width-10;
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
        m_backgrounds[index].setTexture(*ResourcesManager::instance().getGameBackground());
        m_backgrounds[index].setPosition(index * ResourcesManager::instance().getGameBackground()->getSize().x - index, 0);
        m_backgrounds[index].setScale(WINDOW_HEIGHT/m_backgrounds[index].getTexture()->getSize().y, WINDOW_HEIGHT/m_backgrounds[index].getTexture()->getSize().y);
    }
}

sf::Sprite Board::getFirstBackground() const{
    return m_firstBackground;
}

void Board::setFirstBackground() {
    m_firstBackground.setTexture(*ResourcesManager::instance().getFirstBackground());
    m_firstBackground.setScale(WINDOW_HEIGHT/m_firstBackground.getTexture()->getSize().y, WINDOW_HEIGHT/m_firstBackground.getTexture()->getSize().y);
}

float Board::getWidth() const {
    return ResourcesManager::instance().getGameBackground()->getSize().x;
}