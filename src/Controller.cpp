#include "Controller.h"
#include "ResourcesManager.h"
#include "Animation.h"
#include <SFML\GpuPreference.hpp>
#include <iostream>

Controller::Controller() :m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jetpack Joyride"){
   // create();
}

Controller::~Controller() {}

void Controller::create() {
    //sf::Sprite title;
    //title = ResourcesManager::inctance().getTitle();
    //m_window.draw(title);

    sf::Sprite player;
    player = ResourcesManager::inctance().getPlayerSpr();
    m_window.draw(player);

    m_window.display();
}

void Controller::run() {
    sf::Texture animationTexture = ResourcesManager::inctance().getPlayerTex();
    sf::Sprite animationSprite = ResourcesManager::inctance().getPlayerSpr();
   //animationSprite.setScale(sf::Vector2f(20, 20));
    Animation animation(&animationTexture, sf::Vector2u(4, 1), 0.3f);
    float timeDiff = 0.f;
    sf::Clock clock;

    while (m_window.isOpen()){

        timeDiff = clock.restart().asSeconds();
        if (auto event = sf::Event{}; m_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    m_window.close();
                    return;
                }
                //if the user clicks on the window
                case sf::Event::MouseButtonReleased: {
                   // m_music.stop();
                    //handleMouseButton(event.mouseButton);

                }
                case sf::Event::MouseMoved: {
                    //handleMouseMoved(event.mouseMove);
                }
            }
        }
        animation.Update(0, timeDiff);
        animationSprite.setTextureRect(animation.m_objRect);

        m_window.clear(sf::Color::Red);
        m_window.draw(animationSprite);
        m_window.display();
        //create();
    }
}