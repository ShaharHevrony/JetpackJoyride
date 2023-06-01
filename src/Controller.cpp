#include <SFML/Graphics.hpp>
#include <iostream>

#include "Controller.h"
#include "ResourcesManager.h"
#include "PlayGame.h"
#include "Shop.h"
#include "Setting.h"
#include "Help.h"

Controller::Controller() :m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jetpack Joyride") {
    create();
}

Controller::~Controller() {}

void Controller::create() {
    m_window.clear(sf::Color(150, 150, 150));
    m_title.setTexture(*ResourcesManager::instance().getTitle());
    m_title.setPosition(WIDTH_CENTER, TITLE_POSITION);
    m_title.setOrigin(ResourcesManager::instance().getTitle()->getSize().x/2, ResourcesManager::instance().getTitle()->getSize().y/2);
    m_title.setScale(SET_SCALE, SET_SCALE);
    m_window.draw(m_title);

    sf::Sprite tempSpr;
    for(int index = 0; index < NUM_OF_BUTTONS; index++) {
        tempSpr.setTexture(*ResourcesManager::instance().getButtons(index));
        tempSpr.setPosition(WIDTH_CENTER, index * MENU_GAP + HEIGHT_CENTER);
        tempSpr.setOrigin(ResourcesManager::instance().getButtons(index)->getSize().x/2,
                          ResourcesManager::instance().getButtons(index)->getSize().y/2);
        tempSpr.setScale(SET_SCALE, SET_SCALE);
        m_buttonSpr.push_back(tempSpr);
        m_window.draw(m_buttonSpr[index]);
    }
    m_window.display();
}

void Controller::run() {
    while (m_window.isOpen()) {
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
        create();
    }
}

void Controller::handleMouseButton(sf::Event::MouseButtonEvent& event) {
    //get the location of the click
    auto location = m_window.mapPixelToCoords({ event.x, event.y });
    //loop that go on the object in the menu and check if the user click on one of them
    for (int index = 0; index < NUM_OF_BUTTONS; index++) {
        //if the user click on the button
        if (m_buttonSpr[index].getGlobalBounds().contains(location)) {
            switch (index) {
                //if click on eraser
                case PlayButton: {
                    PlayGame* play = new PlayGame(m_window);
                    play->run();
                    break;
                }
                case ShopButton: {
                    Shop shop = Shop();
                    shop.run();
                    break;
                }
                case SettingButton:{
                    try{
                        Setting *setting = new Setting(m_window);
                        setting->run();
                    } catch (std::exception& e){
                        std::cout << e.what() << std::endl;
                        throw;
                    }
                    break;
                }
                case HelpButton:{
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
    m_buttonSpr[m_buttonToScale].setScale(SET_SCALE, SET_SCALE);
    auto location = m_window.mapPixelToCoords({ event.x, event.y });
    for (int row = 0; row < NUM_OF_BUTTONS; row++){
        if (m_buttonSpr[row].getGlobalBounds().contains(location)) {
            m_buttonSpr[row].setScale(SET_SCALE * RESIZE_BUTTONS, SET_SCALE * RESIZE_BUTTONS);
            m_buttonToScale = row;
        }
    }
}
