#include <SFML/Graphics.hpp>
#include "PlayGame.h"
#include "ResourcesManager.h"
#include "Animation.h"


sf::Clock PlayGame::gameTime;

PlayGame::PlayGame(sf::RenderWindow& window) :m_window(&window) {
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
    m_allCoins.resize(NUM_OF_COIN_VEC);
    for (int i = 0; i < 1; i++) { //move
        m_allCoins[i].resize(COINS_LOC[i].size());
        for (int j = 0; j < COINS_LOC[i].size(); j++) {
            Coins tempCoin = Coins(ResourcesManager::instance().getCoinTex(), COINS_LOC[i][j]);
            m_allCoins[i][j] = tempCoin;
        }
    }
}

void PlayGame::createBarry() {
    sf::Vector2f playerPosition(250, 650);
    m_player = Player(ResourcesManager::instance().getPlayerTex(), playerPosition);
}

void PlayGame::createObstical() {
    sf::Vector2f positionA(800, 250);
    sf::Vector2f positionB(800, 540);
    m_obstacle = Obstacle(ResourcesManager::instance().getObstacle(), positionA, positionB, false);
    m_obstacleOpposite = Obstacle(ResourcesManager::instance().getObstacle(), positionB, positionA, true);

}

void PlayGame::createBackGround() {
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

void PlayGame::dealWithCollision()
{
    //check if the player collision with coin
    for (int i = 0; i < 1; i++) { //move
        for (int j = 0; j < COINS_LOC[i].size() ; j++) {
            m_player.handleCollision(m_allCoins[i][j]);
            if (m_allCoins[i][j].getDelete() == true) {
                m_allCoins[i][j].setDelete();
                m_allCoins[i].erase(m_allCoins[i].begin() + j);
                m_allCoins[i].resize(COINS_LOC[i].size());
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
                m_backgroundStartSpr = ResourcesManager::instance().getBackground();
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
            m_background[i].setPosition(m_backgroundX + i * ResourcesManager::instance().getBackgroundTex().getSize().x, 0);
            m_window->draw(m_background[i]);
        }else {
            m_backgroundStartSpr.setPosition(m_backgroundX, 0);
            m_window->draw(m_backgroundStartSpr);
        }
    }

    float time = gameTime.restart().asSeconds();
    //if (m_allCoins[m_coinsGroup][0].getSwitchCoins()) {
      //  m_coinsGroup++;
    //}
    //if (m_coinsGroup >= m_allCoins.size()) {
      //  m_coinsGroup = 0;
   // }

    for (int j = 0; j < m_allCoins[m_coinsGroup].size(); j++) {
        m_allCoins[m_coinsGroup][j].move(time);
        m_window->draw(m_allCoins[m_coinsGroup][j].getObject());
    }

    m_obstacle.animate();
    //m_obstacle.move(time);
    m_window->draw(m_obstacle.getObject());
    m_obstacleOpposite.animate();
    //m_obstacleOpposite.move(time);
    m_window->draw(m_obstacleOpposite.getObject());
    m_player.animate();
    m_player.move(time);
    m_window->draw(m_player.getObject());
    m_window->display();
}