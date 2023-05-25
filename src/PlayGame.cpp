#include <SFML/Graphics.hpp>
#include "PlayGame.h"
#include "ResourcesManager.h"
#include "Animation.h"


sf::Clock PlayGame::gameTime;

PlayGame::PlayGame(sf::RenderWindow& window) :m_window(&window) {
    //writeObjectFile();
    //readObjectFile();
    create();
}

void PlayGame::create(){
    m_backgroundX = 0.0f;

    sf::Vector2f playerPosition2(550,650);
    sf::Texture* tempTexture;
    if (!tempTexture->loadFromFile(PATH + "powering.png")) {
        //throw OpenTextureFailed();
    }
    m_player2 = std::make_shared<Player>(tempTexture, playerPosition2, 2);
    //sf::Vector2f playerPosition(250,650);
    //m_player = std::make_shared<Player>(ResourcesManager::instance().getPlayerTex(), playerPosition, 1);

    //sf::Vector2f testCoinPosition(800, 650);
    //m_coin = std::make_shared<Coins>(ResourcesManager::instance().getCoinTex(), testCoinPosition);

    m_widthBackSize = ResourcesManager::instance().getBackgroundTex().getSize().x;
    m_window->clear();
    m_backgroundStartSpr = ResourcesManager::instance().getBackgroundStartSpr();

    m_backgroundTex = ResourcesManager::instance().getBackgroundTex();
    m_background[0] = ResourcesManager::instance().getBackground();
    m_background[1] = ResourcesManager::instance().getBackground();
    m_background[2] = ResourcesManager::instance().getBackground();

    m_background[0].setPosition(m_backgroundTex.getSize().x, 0);
    m_background[1].setPosition(2 * (m_backgroundTex.getSize().x), 0);
    m_background[2].setPosition(3 * (m_backgroundTex.getSize().x), 0);
    m_window->display();
}

void PlayGame::run() {
    m_start = true;
    sf::Clock loopClock; // Clock to measure loop time
    float elapsedTime = 0.0f;
    float changeInterval = 5.0f;
    float speedTime = 0.0f;
    bool variableChanged = false;

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
            variableChanged = true;
        }

        //update the speed of the background move
        m_backgroundX -= 0.5f + speedTime;
        //if the size of m_backgroundX is bigger than the width of the background
        if ((m_backgroundX <= -(m_widthBackSize)) ) {
            if (m_start) {
                m_backgroundStartSpr = ResourcesManager::instance().getBackground();
                m_backgroundX = 0.0f;
            }
            m_backgroundX = 0.0f;
            m_start = false;
        }
        draw();
    }
}

void PlayGame::draw() {
    m_window->clear();
    for (int i = 0; i < 3; ++i) {
        if (!m_start) {
            m_background[i].setPosition(m_backgroundX + i * ResourcesManager::instance().getBackgroundTex().getSize().x, 0);
            m_window->draw(m_background[i]);
        }else {
            m_backgroundStartSpr.setPosition(m_backgroundX, 0);
            m_window->draw(m_backgroundStartSpr);
        }
    }

    //m_player->animate(1);
    m_player2->animate(2);
    //m_coin->animate(3);
    float time = gameTime.restart().asSeconds();
    //m_player->move(time);
    m_player2->move(time);
    //m_coin->move(time);
    //m_window->draw(m_coin->getObject());
    //m_window->draw(m_player->getObject());
    m_window->draw(m_player2->getObject());
    m_window->display();
    /*
    for(int row = 0; row < m_objectMap.size(); row++) {
        for(int col = 0; col < m_objectMap[row].size(); col++) {
            if(m_objectMap[col][row] != nullptr){
                std::cout << "found a coin here: col - " << col << " , row - " << row  << " and the position is: (x = "
                << m_objectMap[col][row]->getObject().getPosition().x << " , y = "
                << m_objectMap[col][row]->getObject().getPosition().y << ")\n";

                m_window->draw(m_objectMap[col][row]->getObject());
                m_objectMap[col][row]->move(time);
            }
        }
    }
     */
}
/*
void PlayGame::readObjectFile() {
    std::ifstream readingFile;
    const std::string filePath = "GameMap";
    readingFile.open(filePath, std::fstream::in);
    if (!std::filesystem::exists(filePath)) { //Can't open a none existing file
        throw FileNotExist();
    }
    if (!readingFile.is_open()) {             //File doesn't open
        throw OpenFailed();
    }
    m_map.clear();
    std::string str;
    while (!readingFile.eof()) {
        std::getline(readingFile, str);
        m_map.push_back(str);
    }
    readingFile.close();

    m_objectMap.resize(NUM_OF_OBJECTS);
    for(int row = 0; row < m_map.size(); row++) {
        m_objectMap[row].resize(m_map.size());
        for(int col = 0; col < m_map[row].size(); col++) {
            char type = m_map[col][row];
            switch (type) {
                case COIN: {
                    m_objectMap[col][row] = std::make_shared<Coins>(ResourcesManager::instance().getCoinTex(),
                                      sf::Vector2f(WINDOW_WIDTH + 50 * col, 50 * (row % NUM_OF_OBJECTS)));
                    break;
                }
                case SPACE: {
                    break;
                }
            }
        }
    }
}

void PlayGame::writeObjectFile() {
    std::ofstream writingFile;
    if (std::filesystem::exists("GameMap")) {
        //If the file exist then we clear all the file contents and create a new empty file.
        writingFile.open("GameMap", std::ios::out | std::ios::trunc);
    } else {
        writingFile.open("GameMap");
    }

    if (!writingFile.is_open()) {
        throw OpenFailed();
    }
    writingFile << MAP;
    writingFile.close();
}
*/