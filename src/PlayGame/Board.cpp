#include "Board.h"

Board::Board() {
    m_allMaps.clear();
    try {
        writeObjectFile();  // Write object files for each map
        for (int index = 0; index < MAP.size(); index++) {
            readObjectFile(index);  // Read object files for each map
            m_allMaps.insert(m_map);  // Insert the map into the set of all maps
        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        throw;
    }
}

Board::~Board() {}

void Board::writeObjectFile() {
    std::ofstream writingFile;
    for (int index = 0; index < MAP.size(); index++) {
        std::string filePath = "mapNum" + std::to_string(index);
        if (std::filesystem::exists(filePath)) {
            // If the file exists, clear all the file contents and create a new empty file.
            writingFile.open(filePath, std::ios::out | std::ios::trunc);
        }
        else {
            writingFile.open(filePath);
        }

        if (!writingFile.is_open()) {
            throw OpenFileFailed();
        }
        writingFile << MAP[index];  // Write the map data to the file
        writingFile.close();
    }
}

void Board::readObjectFile(int index) {
    m_map.clear();
    std::ifstream readingFile;
    std::string filePath = "mapNum" + std::to_string(index);
    if (!std::filesystem::exists(filePath)) { // Check if the file exists
        throw FileNotExist();
    }
    readingFile.open(filePath, std::fstream::in);
    if (!readingFile.is_open()) {             // Check if the file opened successfully
        throw OpenFileFailed();
    }

    while (!readingFile.eof()) {
        std::string str;
        char my_line[NUM_OF_OBJECTS];
        std::getline(readingFile, str);
        for (int i = 0; i < str.size(); i++) {
            my_line[i] = str[i];
        }
        m_map.push_back(my_line);  // Read each line of the map from the file
    }
    readingFile.close();
}

void Board::draw(sf::RenderWindow* window) {
    for (auto& background : m_backgrounds) {
        window->draw(background);  // Draw the background sprites
    }
    window->draw(m_firstBackground);
    for (auto& nonCollObj : m_nonCollObj) {
        nonCollObj->draw(window);  // Draw non-collidable objects
    }
}

void Board::moveBackgrounds() {
    if (m_speedIncrease >= CHANGE_INTERVAL) {
        m_speed += ACCELERATION;  // Increase the speed if the speed increase threshold is reached
        m_speedIncrease -= CHANGE_INTERVAL;
    }
    m_time = m_loopClock.getElapsedTime().asSeconds();  // Get the elapsed time since the last frame
    m_speedIncrease += m_time;
    m_loopClock.restart();

    m_firstBackground.move(DIRECTION * m_time * m_speed);  // Move the first background sprite
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
        m_backgrounds[index].move(DIRECTION * m_time * m_speed);  // Move the background sprites
        if (m_backgrounds[index].getPosition().x + m_backgrounds[index].getGlobalBounds().width < 0) {
            // If a background sprite goes off the screen, move it to the right side of the screen
            sf::Vector2f position = m_backgrounds[(index + 2) % BACKGROUND].getPosition();
            position.x += m_backgrounds[(index + 2) % BACKGROUND].getGlobalBounds().width - 10;
            m_backgrounds[index].setPosition(position);
        }
    }

    for (auto& nonCollObj : m_nonCollObj) {
        nonCollObj->animate();  // Animate non-collidable objects
        nonCollObj->move(m_time * m_speed);  // Move non-collidable objects
        if (nonCollObj->getObject().getPosition().x <= LAST_POSITION) {
            nonCollObj->setPosition();  // Reset the position of non-collidable objects if they reach a certain position
        }
    }
}

void Board::animate() {
    for (auto& nonCollObj : m_nonCollObj) {
        nonCollObj->animate();  // Animate non-collidable objects
    }
}

std::vector<std::string> Board::getMap() const {
    auto ptr = m_allMaps.begin();
    std::advance(ptr, m_random);
    return *ptr;  // Return a randomly selected map from the set of all maps
}

void Board::setBackgrounds(int size) {
    // Set the texture and scale of the first background sprite
    m_firstBackground.setTexture(*ResourcesManager::instance().getFirstBackground());
    m_firstBackground.setScale(WINDOW_HEIGHT / m_firstBackground.getTexture()->getSize().y, WINDOW_HEIGHT / m_firstBackground.getTexture()->getSize().y);

    sf::Sprite tempBackground;
    float mapLength = 0.f;
    for (int index = 0; index < size; index++) {
        // Create a temporary background sprite
        tempBackground.setTexture(*ResourcesManager::instance().getGameBackground());
        tempBackground.setPosition(index * ResourcesManager::instance().getGameBackground()->getSize().x - index, 0);
        tempBackground.setScale(WINDOW_HEIGHT / tempBackground.getTexture()->getSize().y, WINDOW_HEIGHT / tempBackground.getTexture()->getSize().y);
        m_backgrounds.push_back(tempBackground);  // Add the temporary background sprite to the vector

        mapLength += tempBackground.getPosition().x;  // Calculate the total length of the map
    }

    int space = mapLength / WIDTH_GAP;  // Calculate the number of spaces between non-collidable objects
    int centerMod = 10;  // Modulo value for generating random positions
    int randSci;

    for (int index = 0; index <= space; index++) {
        randSci = 1 + rand() % centerMod;  // Generate a random value for scientist position
        sf::Vector2f lightPosition = sf::Vector2f(WINDOW_WIDTH + index * WIDTH_CENTER * tempBackground.getScale().y, GAME_SETTING_Y);
        // Create a Light object and add it to the non-collidable objects vector
        m_nonCollObj.push_back(std::make_unique<Light>(ResourcesManager::instance().getLights(), lightPosition));

        sf::Vector2f scientistPosition = sf::Vector2f(WINDOW_WIDTH + randSci * randSci * tempBackground.getScale().y, WINDOW_HEIGHT / 1.28);
        // Create a Scientist object and add it to the non-collidable objects vector
        m_nonCollObj.push_back(std::make_unique<Scientist>(ResourcesManager::instance().getScientist(), scientistPosition));
    }
}

void Board::randMap() {
    srand(time(nullptr));  // Seed the random number generator with the current time
    m_random = rand() % MAP.size();  // Generate a random map index
    if (m_mapCount.size() != MAP.size()) {
        while (m_mapCount.contains(m_random)) {
            // If the randomly generated index is already present in the map count set,
            // generate a new random index until a unique one is found
            m_random = rand() % MAP.size();
        }
        m_mapCount.insert(m_random);  // Add the random index to the map count set
    }
    else {
        m_mapCount.clear();  // If all maps have been used, clear the map count set
    }
}

float Board::getTime() const {
    return m_time;  // Return the elapsed time
}

float Board::getMovement() const {
    return m_time * m_speed;  // Return the movement distance based on time and speed
}

void Board::setClock() {
    m_loopClock.restart();  // Restart the clock to measure the elapsed time
}
