#include <SFML/Graphics.hpp>
#include "PlayGame.h"
#include "ResourcesManager.h"
#include "Animation.h"

sf::Clock PlayGame::gameTime;

PlayGame::PlayGame(sf::RenderWindow& window) :m_window(&window) {
    create();
}

void PlayGame::create(){
    sf::Vector2f position(200,800);
    m_player = std::make_shared<Player>(ResourcesManager::instance().getPlayerTex(), position);
    m_player->setObject(ResourcesManager::instance().getPlayerSpr());
    m_window->clear(sf::Color(150,150,150));
    m_window->display();
}

void PlayGame::run() {
    while (m_window->isOpen()){
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    m_window->close();
                    return;
                }
            }
        }
        m_window->clear(sf::Color(150,150,150));
        m_player->animate();
        float time = gameTime.restart().asSeconds();
        m_player->move(time);
        m_window->draw(m_player->getObject());
        m_window->display();
    }
}