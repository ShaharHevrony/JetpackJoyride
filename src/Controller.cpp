#include <SFML/Graphics.hpp>
#include <iostream>

#include "Controller.h"
#include "ResourcesManager.h"
#include "Animation.h"

#include "PlayGame.h"
#include "Shop.h"
#include "Setting.h"
#include "Help.h"

Controller::Controller() :m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jetpack Joyride"){
    create();
}

Controller::~Controller() {}

void Controller::create() {
    m_window.clear(sf::Color(150,150,150));
    m_titleSpr = ResourcesManager::inctance().getTitle();
    m_titleSpr.setPosition(SCREEN_CENTER, 230);
    m_titleSpr.setOrigin(TITLE_WIDTH/2, TITLE_HEIGHT/2);
    m_window.draw(m_titleSpr);

    sf::Sprite tempSpr;
    for(int index = 0; index < 4; index++){
        m_buttonsTex[index] = ResourcesManager::inctance().getButtonsTex(index);
        sf::Texture* tempTex = &m_buttonsTex[index];
        tempSpr.setTexture(*tempTex);
        tempSpr.setPosition(SCREEN_CENTER, index * MENU_GAP + MENU_START_ROW);
        tempSpr.setOrigin(MENU_PIC_WIDTH / 2, MENU_PIC_HEIGHT / 2);
        m_buttonSpr.push_back(tempSpr);
        m_window.draw(m_buttonSpr[index]);
    }

    //sf::Sprite player;
    //player = ResourcesManager::inctance().getPlayerSpr();
    //m_window.draw(player);
    m_window.display();
}

void Controller::run() {
    //sf::Texture animationTexture = ResourcesManager::inctance().getPlayerTex();
    //sf::Sprite animationSprite = ResourcesManager::inctance().getPlayerSpr();
    //Animation animation(&animationTexture, sf::Vector2u(4, 1), 0.3f);
    //float timeDiff = 0.f;
    //sf::Clock clock;
    //sf::View view (sf::Vector2f(0.f,0.f), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    //view.setCenter(m_titleSpr.getPosition());
    //m_window.setView(view);

    while (m_window.isOpen()){
        //timeDiff = clock.restart().asSeconds();
        if (auto event = sf::Event{}; m_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    m_window.close();
                    return;
                }
                    //if the user clicks on the window
                case sf::Event::MouseButtonReleased: {
                    handleMouseButton(event.mouseButton);

                }
                case sf::Event::MouseMoved: {
                    handleMouseMoved(event.mouseMove);
                }
            }
        }
        //animation.Update(0, timeDiff);
        //animationSprite.setTextureRect(animation.m_objRect);
        //m_window.draw(animationSprite);
        create();
    }
}

void Controller::handleMouseButton(sf::Event::MouseButtonEvent& event) {
    //get the location of the click
    auto location = m_window.mapPixelToCoords({ event.x, event.y });
    //loop that go on the object in the menu and check if the user click on one of them
    for (int index = 0; index < 4; index++) {
        //if the user click on the button
        if (m_buttonSpr[index].getGlobalBounds().contains(location)) {
            switch (index) {
                //if click on eraser
                case playButton: {
                    PlayGame* play = new PlayGame(m_window);
                    play->run();
                    break;
                }
                case shopButton: {
                    Shop shop = Shop();
                    shop.run();
                    break;
                }
                case settingButton:{
                    Setting setting = Setting();
                    setting.run();
                    break;
                }
                case helpButton:{
                    Help help = Help();
                    help.run();
                    break;
                }
                default:
                    break;
            }
        }
    }
}

void Controller::handleMouseMoved(sf::Event::MouseMoveEvent& event) {
    m_buttonSpr[m_buttonToScale].setScale(1, 1);
    auto location = m_window.mapPixelToCoords({ event.x, event.y });
    for (int row = 0; row < 4; row++){
        if (m_buttonSpr[row].getGlobalBounds().contains(location)) {
            m_buttonSpr[row].setScale(1.15, 1.15);
            m_buttonToScale = row;
        }
    }
}