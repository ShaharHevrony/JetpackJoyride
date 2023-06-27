#include "Board.h"

sf::Clock Board::loopClock;

Board::Board() {
    m_allMaps.clear();
    loopClock.restart();
    try {
        readObjectFile();   //Read object files for each map
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        throw;
    }
}

Board::~Board() {}

void Board::readObjectFile() {
    for (int index = 0; index < MAP_SIZE; index++) {
        m_map.clear();
        std::ifstream readingFile;
        std::string filePath = "mapNum" + std::to_string(index) + ".txt";
        if (!std::filesystem::exists(filePath)) { //Check if the file exists
            throw FileNotExist();
        }
        readingFile.open(filePath, std::fstream::in);
        if (!readingFile.is_open()) {             //Check if the file opened successfully
            throw OpenFileFailed();
        }

        while (!readingFile.eof()) {
            std::string str;
            char my_line[NUM_OF_OBJECTS];
            std::getline(readingFile, str);
            for (int i = 0; i < str.size(); i++) {
                my_line[i] = str[i];
            }
            m_map.push_back(my_line); //Read each line of the map from the file
        }
        readingFile.close();
        m_allMaps.insert(m_map);     //Insert the map into the set of all maps
    }
}

void Board::draw(sf::RenderWindow* window) {
    for (auto& background : m_backgrounds) {
        window->draw(background);  //Draw the background sprites
    }
    window->draw(m_firstBackground);
    for (auto& nonCollLight : m_nonCollLights) {
        nonCollLight->draw(window);  //Draw non-collidable objects
    }

    for (auto& nonCollSci : m_nonCollScis) {
        nonCollSci->draw(window);  //Draw non-collidable objects
    }
}

void Board::moveBackgrounds() {
    if (m_speedIncrease >= CHANGE_INTERVAL) {
        m_speed += ACCELERATION;  //Increase the speed if the speed increase threshold is reached
        m_speedIncrease -= CHANGE_INTERVAL;
    }
    m_time = loopClock.getElapsedTime().asSeconds();
    m_speedIncrease += m_time;
    loopClock.restart();

    m_firstBackground.move(DIRECTION * m_time * m_speed);  //Move the first background sprite
    if (m_firstBackground.getPosition().x > -(WINDOW_WIDTH)) {
        //Move the second background sprite based on the first one
        sf::Vector2f position = m_backgrounds[FIRST].getPosition();
        position.x = m_firstBackground.getPosition().x + m_firstBackground.getGlobalBounds().width;
        m_backgrounds[FIRST].setPosition(position);
        //Move the third background sprite based on the second one
        position = m_backgrounds[SECOND].getPosition();
        position.x = m_backgrounds[FIRST].getPosition().x + m_backgrounds[FIRST].getGlobalBounds().width;
        m_backgrounds[SECOND].setPosition(position);
    }

    for (int index = 0; index < THIRD; index++) {
        m_backgrounds[index].move(DIRECTION * m_time * m_speed);  //Move the background sprites
        if (m_backgrounds[index].getPosition().x + m_backgrounds[index].getGlobalBounds().width < ZERO) {
            //If a background sprite goes off the screen, move it to the right side of the screen
            sf::Vector2f position = m_backgrounds[(index + SECOND) % BACKGROUND].getPosition();
            position.x += m_backgrounds[(index + SECOND) % BACKGROUND].getGlobalBounds().width - TEN;
            m_backgrounds[index].setPosition(position);
        }
    }
    moveNonColl(true);
}

void Board::animate() {
    for (auto& nonCollLight : m_nonCollLights) {
        nonCollLight->animate(); //Animate non-collidable objects
    }
    for (auto& nonCollSci : m_nonCollScis) {
        nonCollSci->animate();   //Animate non-collidable objects
    }
}

std::vector<std::string> Board::getMap() const {
    auto ptr = m_allMaps.begin();
    std::advance(ptr, m_random);
    return *ptr;  //Return a randomly selected map from the set of all maps
}

void Board::setBackgrounds() {
    //Set the texture and scale of the first background sprite
    m_firstBackground.setTexture(*ResourcesManager::instance().getFirstBackground());
    m_firstBackground.setScale(WINDOW_HEIGHT / m_firstBackground.getTexture()->getSize().y, WINDOW_HEIGHT / m_firstBackground.getTexture()->getSize().y);

    sf::Sprite tempBackground;
    float mapLength = 0.f;
    for (int index = 0; index < BACKGROUND; index++) {
        //Create a temporary background sprite
        tempBackground.setTexture(*ResourcesManager::instance().getGameBackground());
        tempBackground.setPosition(index * ResourcesManager::instance().getGameBackground()->getSize().x - index, 0);
        tempBackground.setScale(WINDOW_HEIGHT / tempBackground.getTexture()->getSize().y, WINDOW_HEIGHT / tempBackground.getTexture()->getSize().y);
        m_backgrounds.push_back(tempBackground);     //Add the temporary background sprite to the vector
        mapLength += tempBackground.getPosition().x; //Calculate the total length of the map
    }
    int space = mapLength / WIDTH_GAP; //Calculate the number of spaces between non-collidable objects
    int centerMod = TEN;               //Modulo value for generating random positions
    int randSci;
    for (int index = FIRST; index <= space; index++) {
        randSci = FIRST + rand() % centerMod; //Generate a random value for scientist position
        sf::Vector2f lightPosition = sf::Vector2f(WINDOW_WIDTH + index * WIDTH_CENTER * tempBackground.getScale().y, GAME_SETTING_Y);
        //Create a Light object and add it to the non-collidable objects vector
        m_nonCollLights.push_back(std::make_unique<Light>(ResourcesManager::instance().getLights(), lightPosition));
        sf::Vector2f scientistPosition = sf::Vector2f(WINDOW_WIDTH + randSci * randSci * tempBackground.getScale().y, WINDOW_HEIGHT / 1.28);
        //Create a Scientist object and add it to the non-collidable objects vector
        m_nonCollScis.push_back(std::make_unique<Scientist>(ResourcesManager::instance().getScientist(), scientistPosition));
    }
}

void Board::randMap() {
    srand(time(nullptr));           //Seed the random number generator with the current time
    m_random = rand() % MAP_SIZE;   //Generate a random map index
    if (m_mapCount.size() != MAP_SIZE) {
        while (m_mapCount.contains(m_random)) {
            //If the randomly generated index is already present in the map count set, generate a new random index until a unique one is found
            m_random = rand() % MAP_SIZE;
        }
        m_mapCount.insert(m_random); //Add the random index to the map count set
    }
    else {
        m_mapCount.clear();         //If all maps have been used, clear the map count set
    }
}

//Return the elapsed time
float Board::getTime() const {
    return m_time;
}

//Return the movement distance based on time and speed
float Board::getMovement() const {
    return m_time * m_speed;
}

//Restart the clock to measure the elapsed time
void Board::setClock() {
    loopClock.restart();
}

void Board::moveNonColl(bool alive) {
    for (auto& nonCollSci : m_nonCollScis) {
        nonCollSci->animate();                       //Animate non-collidable objects
        if (!alive) {
            nonCollSci->move(m_time * ACCELERATION); //Move non-collidable objects
        } else {
            nonCollSci->move(m_time * m_speed);     //Move non-collidable objects
        }
        if (nonCollSci->getObject().getPosition().x <= LAST_POSITION) {
            nonCollSci->setPosition();              //Reset the position of non-collidable objects if they reach a certain position
        }
    }
    if (alive) {
        for (auto& nonCollLight : m_nonCollLights) {
            nonCollLight->animate();              //Animate non-collidable objects
            nonCollLight->move(m_time * m_speed); //Move non-collidable objects
            if (nonCollLight->getObject().getPosition().x <= LAST_POSITION) {
                nonCollLight->setPosition();      //Reset the position of non-collidable objects if they reach a certain position
            }
        }
    }
}