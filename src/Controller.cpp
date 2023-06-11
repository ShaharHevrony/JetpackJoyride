#include <SFML/Graphics.hpp>
#include <iostream>

#include "Controller.h"
#include "ResourcesManager.h"
#include "PlayGame.h"
#include "Shop.h"
#include "Setting.h"
#include "Help.h"

GameControllerInfo::GameControllerInfo() {
    ChosenCharacter = 0;
    CollectedSum = 0;
    MusicVolume = 0;
    SoundVolume = 0;
    for(int top = 0; top < TOP_FIVE; top++){
        TopScore[top] = 0;
    }
}

Controller::Controller() :m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jetpack Joyride") {
    create();
}

Controller::~Controller() {}

void Controller::create() {
    m_gameController = GameControllerInfo();

    m_menuBackground.setTexture(*ResourcesManager::instance().getGameMenu());
    m_menuBackground.setScale(WINDOW_WIDTH/m_menuBackground.getTexture()->getSize().x, WINDOW_HEIGHT/m_menuBackground.getTexture()->getSize().y);
    m_title.setTexture(*ResourcesManager::instance().getTitle());
    m_title.setPosition(WIDTH_CENTER, TITLE_POSITION);
    m_title.setOrigin(ResourcesManager::instance().getTitle()->getSize().x/2, ResourcesManager::instance().getTitle()->getSize().y/2);
    m_title.setScale(SET_SCALE, SET_SCALE);

    sf::Sprite tempSpr;
    for(int button = 0; button < 8; button++) {
        tempSpr.setTexture(*ResourcesManager::instance().getButtons(button));
        if((button % 4) == PlayButton){
            tempSpr.setPosition(WIDTH_CENTER - MENU_WIDTH_GAP, HEIGHT_CENTER);
        } else if((button % 4) == ShopButton) {
            tempSpr.setPosition(WIDTH_CENTER + MENU_WIDTH_GAP, HEIGHT_CENTER);
        } else if((button % 4) == SettingButton) {
            tempSpr.setPosition(WIDTH_CENTER - MENU_WIDTH_GAP, HEIGHT_CENTER + MENU_HEIGHT_GAP);
        } else {
            tempSpr.setPosition(WIDTH_CENTER + MENU_WIDTH_GAP, HEIGHT_CENTER + MENU_HEIGHT_GAP);
        }
        tempSpr.setOrigin(ResourcesManager::instance().getButtons(button)->getSize().x/2,ResourcesManager::instance().getButtons(button)->getSize().y/2);
        tempSpr.setScale(SET_BUTTONS, SET_BUTTONS);
        m_getButtonSpr.push_back(tempSpr);
    }
    for(int button = 0; button < NUM_OF_BUTTONS; button++){
        m_gameButtons.push_back(m_getButtonSpr[button]);
    }
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
        draw();
    }
}

void Controller::draw() {
    m_window.clear();
    m_window.draw(m_menuBackground);
    m_window.draw(m_title);
    for(int index = 0; index < NUM_OF_BUTTONS; index++){
        m_window.draw(m_gameButtons[index]);
    }
    m_window.display();
}

void Controller::handleMouseButton(sf::Event::MouseButtonEvent& event) {
    //get the location of the click
    auto location = m_window.mapPixelToCoords({ event.x, event.y });
    //loop that go on the object in the menu and check if the user click on one of them
    for (int index = 0; index < NUM_OF_BUTTONS; index++) {
        //if the user click on the button
        if (m_gameButtons[index].getGlobalBounds().contains(location)) {
            switch (index) {
                //if click on eraser
                case PlayButton: {
                    PlayGame* play = new PlayGame(m_window);
                    if (!m_music.openFromFile(PATH + "JetpackJoyrideMusic.wav")) {
                        //Error loading music file
                    }
                    m_music.setVolume(m_musicSound);
                    m_music.play();
                    m_music.setLoop(true); // set the music to loop
                    play->run();
                    m_music.stop();
                    break;
                }
                case ShopButton: {
                    m_gameController.CollectedSum = 10000;
                    Shop* shop = new Shop(m_window);
                    shop->run(m_gameController);
                    break;
                }
                case SettingButton:{
                    try{
                        Setting *setting = new Setting(m_window);
                        setting->run();
                        m_musicSound = setting->getVol();

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
    for(int button = 0; button < NUM_OF_BUTTONS; button++){
        m_gameButtons[button] = (m_getButtonSpr[button]);
    }

    auto location = m_window.mapPixelToCoords({ event.x, event.y });
    for (int button = 0; button < NUM_OF_BUTTONS; button++){
        if (m_gameButtons[button].getGlobalBounds().contains(location)) {
            m_gameButtons[button].setTexture(*m_getButtonSpr[button + 4].getTexture());
        }
    }
}

void Controller::setGameControllerInfo(GameControllerInfo gameController) {
    m_gameController = gameController;
}

GameControllerInfo Controller::getGameControllerInfo() {
    return m_gameController;
}