#include <SFML/Graphics.hpp>
#include "PlayGame.h"

sf::Clock PlayGame::gameTime;

PlayGame::PlayGame(sf::RenderWindow& window) : m_window(&window) {}

PlayGame::~PlayGame() {}

void PlayGame::create() {
    createBarry();
    createObjectMap();
    m_board.setFirstBackground();
    m_board.setBackgrounds(BACKGROUND);
}

void PlayGame::createBarry(){
    sf::Vector2f playerPosition(250, 650);
    m_player = Player(ResourcesManager::instance().getPlayer(), playerPosition);
}

void PlayGame::createObjectMap(){
    srand(time(nullptr));
    int randMap = rand() % MAP.size();
    //int randMap = 1;
    sf::Vector2f position;
    for(int row = 0; row < m_board.getMap(randMap).size(); row++) {
        for(int col = 0; col < NUM_OF_OBJECTS; col++) {
            char type = m_board.getMap(randMap)[row][col];
            switch (type) {
                case COIN: {
                    position = sf::Vector2f(WINDOW_WIDTH + 50 * row, 60 + 50 * col);
                    m_singleObjects.push_back(std::make_unique<Coin>(ResourcesManager::instance().getCoin(), position));
                    break;
                }
                case OBSTACLE:{
                    position = sf::Vector2f(WINDOW_WIDTH + 60 * row, 50 + 60 * col);
                    m_pairedObjects.push_back(std::make_unique<Obstacle>(ResourcesManager::instance().getObstacle(), position));
                    if(m_pairedObjects.size() % 2 == 0){
                        m_pairedObjects[m_pairedObjects.size()-2]->setPaired(position);
                        m_pairedObjects[m_pairedObjects.size()-1]->setPaired(m_pairedObjects[m_pairedObjects.size()-2]->getObject().getPosition());
                    }
                    break;
                }
                case SPACE:{
                    break;
                }
            }
        }
    }
}

void PlayGame::run() {
    create();
    while (m_window->isOpen()){
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    m_window->close();
                    return;
                }
            }
        }
        draw();
    }
}

void PlayGame::dealWithCollision(){
    //check if the player collision with coins
    for (int i = 0; i < m_singleObjects.size(); i++) {
        m_player.handleCollision(*m_singleObjects[i]);
        if (m_singleObjects[i]->getDelete() == true) {
            m_singleObjects[i]->setDelete();
            m_singleObjects.erase(m_singleObjects.begin() + i);
            m_singleObjects.resize(COINS_LOC[i].size());
        }
    }
    //check if the player collision with obstacles
    for (int i = 0; i < m_pairedObjects.size(); i++) {
        m_player.handleCollision(*m_pairedObjects[i]);
        if (m_pairedObjects[i]->getDelete() == true) {
            m_pairedObjects[i]->setDelete();
            m_pairedObjects.erase(m_pairedObjects.begin() + i);
            m_pairedObjects.resize(COINS_LOC[i].size());
        }
    }
}

void PlayGame::draw(){
    m_window->clear();
    // Calculate the elapsed time in seconds
    float loopTime = m_control.LoopClock_t.getElapsedTime().asSeconds();
    m_control.ElapsedTime_t += loopTime;
    m_control.LoopClock_t.restart();
    //every 5 seconds update the speed
    if (m_control.ElapsedTime_t >= m_control.ChangeInterval_t) {
        m_control.SpeedTime_t += 0.01f;
        m_control.ElapsedTime_t -= m_control.ChangeInterval_t;
    }

    //update the speed of the background move
    m_control.BackgroundSpeed_t -= 0.5f + m_control.SpeedTime_t;
    //if the size of m_backgroundX is bigger than the width of the background
    if (m_control.BackgroundSpeed_t <= -(m_board.getWidth())) {
        if (m_control.Start_t) {
            m_board.setFirstBackground();
        }
        m_control.BackgroundSpeed_t = 0.0f;
        m_control.Start_t = false;
    }

    for (int i = 0; i < BACKGROUND; ++i) {
        if (!m_control.Start_t) {
            m_board.setBackgroundPosition(i, sf::Vector2f (m_control.BackgroundSpeed_t + i * ResourcesManager::instance().getBackground()->getSize().x, 0));
            m_window->draw(m_board.getBackgrounds()[i]);
        }else {
            m_board.setFirstBackgroundPosition(sf::Vector2f (m_control.BackgroundSpeed_t, 0));
            m_window->draw(m_board.getFirstBackground());
        }
    }

    moveObjects();
    for(int index = 0; index < m_pairedObjects.size(); index++){
        if(index != m_pairedObjects.size()-1 || m_pairedObjects.size() % 2 == 0){
            m_window->draw(m_pairedObjects[index]->getObject());
        }
    }
    for (int row = 0; row < m_singleObjects.size(); row++) {
        m_window->draw(m_singleObjects[row]->getObject());
    }
    m_window->draw(m_player.getObject());
    m_window->display();
}

void PlayGame::moveObjects(){
    float time = gameTime.restart().asSeconds();
    for(int index = 0; index < m_pairedObjects.size(); index++){
        if(index != m_pairedObjects.size()-1 || m_pairedObjects.size() % 2 == 0){
            m_pairedObjects[index]->animate();
            m_pairedObjects[index]->move(time);
        }
    }

    for (int index = 0; index < m_singleObjects.size(); index++) {
        m_singleObjects[index]->animate();
        m_singleObjects[index]->move(time);
    }
    m_player.animate();
    m_player.move(time);
    dealWithCollision();
}