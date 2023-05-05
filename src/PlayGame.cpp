#include <SFML/Graphics.hpp>

#include "PlayGame.h"
#include "ResourcesManager.h"
#include "Animation.h"
PlayGame::PlayGame(sf::RenderWindow& window) :m_window(&window) {}

void PlayGame::create(){
    sf::Sprite player;
    player = ResourcesManager::inctance().getPlayerSpr();
    m_window->draw(player);
    m_window->display();
}
void PlayGame::run() {
    killBarry();
}

void PlayGame::killBarry(){
    sf::Texture animationTexture = ResourcesManager::inctance().getPlayerTex();
    sf::Sprite animationSprite = ResourcesManager::inctance().getPlayerSpr();
    Animation animation(&animationTexture, sf::Vector2u(4, 1), 0.3f);
    float timeDiff = 0.f;
    sf::Clock clock;

    while (m_window->isOpen()){
        sf::Event event;
        while (m_window->pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                m_window->close();
                return;
            }
        }
        timeDiff = clock.restart().asSeconds();
        animation.Update(0, timeDiff);
        animationSprite.setTextureRect(animation.m_objRect);
        m_window->clear(sf::Color(150,150,150));
        m_window->draw(animationSprite);
        m_window->display();
    }
}