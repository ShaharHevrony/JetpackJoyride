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

    sf::Vector2f PlayetPosition(250,650);
    m_player = std::make_shared<Player>(ResourcesManager::instance().getPlayerTex(), PlayetPosition);
    sf::Vector2f testCoinPosition(700, 650);
    m_coin = std::make_shared<Coins>(ResourcesManager::instance().getCoinTex(), testCoinPosition);
    m_wigthBackSize = ResourcesManager::instance().getBachgroundTex().getSize().x;
    m_window->clear();
    m_backgroundStartSpr = ResourcesManager::instance().getBachgroundStartSpr();

    m_backgroundTex = ResourcesManager::instance().getBachgroundTex();
    m_background[0] = ResourcesManager::instance().getBachground();
    m_background[1] = ResourcesManager::instance().getBachground();
    m_background[2] = ResourcesManager::instance().getBachground();
    //m_backgroundStartSpr.setPosition(0,0);

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
        //every 5 second update the speed 
        if (elapsedTime >= changeInterval) {
            speedTime += 0.1f;
        elapsedTime -= changeInterval;
        variableChanged = true;
    }


        //update the speed of the background move
        m_backgroundX -= 1.0f + speedTime;
        //if the size of m_backgroundX is biger than the wigth of the backround 
        if ((m_backgroundX <= -(m_wigthBackSize)) ) {
            if (m_start) {
                m_backgroundStartSpr = ResourcesManager::instance().getBachground();
                m_backgroundX = 0.0f;
            }
            m_backgroundX = 0.0f;
            m_start = false;
        }

        draw();
    }
}

void PlayGame::draw()
{
    m_window->clear();

    for (int i = 0; i < 3; ++i) {
        if (!m_start) {
            m_background[i].setPosition(m_backgroundX + i * ResourcesManager::instance().getBachgroundTex().getSize().x, 0);
            m_window->draw(m_background[i]);
        }else {
            m_backgroundStartSpr.setPosition(m_backgroundX  , 0);
            m_window->draw(m_backgroundStartSpr);
        }

    }

    m_player->animate();
    m_coin->animate();
    float time = gameTime.restart().asSeconds();
    m_player->move(time);
    m_coin->move(time);
    m_window->draw(m_coin->getObject());
    m_window->draw(m_player->getObject());
    m_window->display();
}
