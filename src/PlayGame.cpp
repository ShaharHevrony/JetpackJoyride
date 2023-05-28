#include <SFML/Graphics.hpp>
#include "PlayGame.h"
#include "ResourcesManager.h"
#include "Animation.h"


sf::Clock PlayGame::gameTime;

PlayGame::PlayGame(sf::RenderWindow& window) :m_window(&window) {
    writeObjectFile();
    readObjectFile();
    create();
}

void PlayGame::create(){
    m_backgroundX = 0.0f;
    createCoin();
    createBarry();
    createObstical();
    createBackGround();
}
void PlayGame::createCoin() {

}

void PlayGame::createBarry() {
    sf::Vector2f playerPosition(250, 650);
    m_player = Player(ResourcesManager::instance().getPlayer(), playerPosition);
}

void PlayGame::createObstical() {
    sf::Vector2f positionA(800, 250);
    sf::Vector2f positionB(800, 540);
    m_obstacle = Obstacle(ResourcesManager::instance().getObstacle(), positionA, positionB, false);
    m_obstacleOpposite = Obstacle(ResourcesManager::instance().getObstacle(), positionB, positionA, true);

}

void PlayGame::createBackGround() {
    m_widthBackSize = ResourcesManager::instance().getBackground()->getSize().x;
    m_window->clear();
    m_firstBackground.setTexture(*ResourcesManager::instance().getFirstBackground());

    m_background[0].setTexture(*ResourcesManager::instance().getBackground());
    m_background[1].setTexture(*ResourcesManager::instance().getBackground());
    m_background[2].setTexture(*ResourcesManager::instance().getBackground());

    m_background[0].setPosition(ResourcesManager::instance().getBackground()->getSize().x, 0);
    m_background[1].setPosition(2 * (ResourcesManager::instance().getBackground()->getSize().x), 0);
    m_background[2].setPosition(3 * (ResourcesManager::instance().getBackground()->getSize().x), 0);
    m_window->display();
}

void PlayGame::dealWithCollision() {
    //check if the player collision with coin
    for (int i = 0; i < 1; i++) { //move
        for (int j = 0; j < COINS_LOC[i].size() ; j++) {
            m_player.handleCollision(m_objectMap[i][j]);
            if (m_objectMap[i][j].getDelete() == true) {
                m_objectMap[i][j].setDelete();
                m_objectMap[i].erase(m_objectMap[i].begin() + j);
                m_objectMap[i].resize(COINS_LOC[i].size());
            }
        }
    }
}
void PlayGame::run() {
    m_start = true;
    sf::Clock loopClock; // Clock to measure loop time
    float elapsedTime = 0.0f;
    float changeInterval = 5.0f;
    float speedTime = 0.0f;

    while (m_window->isOpen()){
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    m_window->close();
                    return;
                }
            }
        }
        // Calculate the elapsed time in seconds
        float loopTime = loopClock.getElapsedTime().asSeconds();
        elapsedTime += loopTime;
        loopClock.restart();
        //every 5 seconds update the speed
        if (elapsedTime >= changeInterval) {
            speedTime += 0.01f;
            elapsedTime -= changeInterval;
        }

        //update the speed of the background move
        m_backgroundX -= 0.5f + speedTime;
        //if the size of m_backgroundX is bigger than the width of the background
        if ((m_backgroundX <= -(m_widthBackSize)) ) {
            if (m_start) {
                m_firstBackground.setTexture(*ResourcesManager::instance().getFirstBackground());
            }
            m_backgroundX = 0.0f;
            m_start = false;
        }
        dealWithCollision();
        draw();
    }
}

void PlayGame::draw() {
    m_window->clear();
    for (int i = 0; i < 3; ++i) {
        if (!m_start) {
            m_background[i].setPosition(m_backgroundX + i * ResourcesManager::instance().getBackground()->getSize().x, 0);
            m_window->draw(m_background[i]);
        }else {
            m_firstBackground.setPosition(m_backgroundX, 0);
            m_window->draw(m_firstBackground);
        }
    }

    float time = gameTime.restart().asSeconds();
    for (int row = 0; row < m_objectMap.size(); row++) {
        for (int col = 0; col < m_objectMap[row].size(); col++) {
            m_objectMap[row][col].move(time);
            m_window->draw(m_objectMap[row][col].getObject());
        }
    }
    m_obstacle.animate();
    m_obstacle.move(time);
    m_window->draw(m_obstacle.getObject());

    m_obstacleOpposite.animate();
    m_obstacleOpposite.move(time);
    m_window->draw(m_obstacleOpposite.getObject());

    m_player.animate();
    m_player.move(time);
    m_window->draw(m_player.getObject());

    m_window->display();
}

void PlayGame::readObjectFile() {
    std::ifstream readingFile;
    const std::string filePath = "GameMap";
    if (!std::filesystem::exists(filePath)) { //Can't open a none existing file
        throw FileNotExist();
    }

    readingFile.open(filePath, std::fstream::in);
    if (!readingFile.is_open()) {             //File doesn't open
        throw OpenFailed();
    }
    m_map.clear();

    do {
        std::string str;
        char my_line[NUM_OF_OBJECTS];
        std::getline(readingFile, str);
        for (int i = 0; i < str.size(); i++) {
            my_line[i] = str[i];
        }
        m_map.push_back(my_line);
    } while (!readingFile.eof());
    readingFile.close();

    for(int row = 0; row < m_map.size(); row++) {
        std::vector<Coins> tempVector;
        for(int col = 0; col < m_map[col].size(); col++) {
            char type = m_map[row][col];
            switch (type) {
                case COIN: {
                    Coins tempCoin = Coins(ResourcesManager::instance().getCoin(), sf::Vector2f(WINDOW_WIDTH + 50 * row, 60 + 50 * (col % NUM_OF_OBJECTS)));
                    tempVector.push_back(tempCoin);
                    break;
                }
                case OBSTACLE:{
                    break;
                }
                case SPACE: {
                    break;
                }
            }
        }
        m_objectMap.push_back(tempVector);
    }
}

void PlayGame::writeObjectFile() {

    std::ofstream writingFile;
    if (std::filesystem::exists("GameMap")) {
        //If the file exist then we clear all the file contents and create a new empty file.
        writingFile.open("GameMap", std::ios::out | std::ios::trunc);
    }
    else {
        writingFile.open("GameMap");
    }

    if (!writingFile.is_open()) {
        throw OpenFailed();
    }
    writingFile << MAP;
    writingFile.close();

}
