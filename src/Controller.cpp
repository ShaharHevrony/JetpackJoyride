#include <SFML/Graphics.hpp>

#include "Controller.h"
#include "ResourcesManager.h"
#include "PlayGame.h"
#include "Shop.h"
#include "Settings.h"
#include "Help.h"

Controller::Controller() :m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jetpack Joyride", sf::Style::Close | sf::Style::Titlebar) {
    create();
    sf::Image image = (*ResourcesManager::instance().getIcon());
    m_window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    std::cout << "Width: " << sf::VideoMode::getDesktopMode().width << ", Height: " << sf::VideoMode::getDesktopMode().height << ", Height RATIO: " << HEIGHT_RATIO<< "\n";
}

Controller::~Controller() {}

void Controller::create() {
    m_menuBackground.setTexture(*ResourcesManager::instance().getGameMenu());
    float scale = std::max(WINDOW_WIDTH/m_menuBackground.getTexture()->getSize().x,  WINDOW_HEIGHT/m_menuBackground.getTexture()->getSize().y);
    m_menuBackground.setScale(scale, scale);
    m_title.setTexture(*ResourcesManager::instance().getTitle());
    m_title.setPosition(WIDTH_CENTER, TITLE_POSITION);
    m_title.setOrigin(ResourcesManager::instance().getTitle()->getSize().x/2, ResourcesManager::instance().getTitle()->getSize().y/2);
    m_title.setScale(PLAYER_SCALE, PLAYER_SCALE);

    sf::Sprite tempSpr;
    for(int button = 0; button < 8; button++) {
        tempSpr.setTexture(*ResourcesManager::instance().getButtons(button));
        if((button % 4) == PlayButton){
            tempSpr.setPosition(WIDTH_CENTER - WIDTH_GAP, HEIGHT_CENTER);
        } else if((button % 4) == ShopButton) {
            tempSpr.setPosition(WIDTH_CENTER + WIDTH_GAP, HEIGHT_CENTER);
        } else if((button % 4) == SettingButton) {
            tempSpr.setPosition(WIDTH_CENTER - WIDTH_GAP, HEIGHT_CENTER + HEIGHT_GAP);
        } else {
            tempSpr.setPosition(WIDTH_CENTER + WIDTH_GAP, HEIGHT_CENTER + HEIGHT_GAP);
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
                    m_music.setVolume(GameManager::instance().getMusic());
                    m_music.play();
                    m_music.setLoop(true); // set the music to loop
                    play->run();
                    m_music.stop();
                    break;
                }
                case ShopButton: {
                    Shop* shop = new Shop(m_window);
                    shop->run();
                    break;
                }
                case SettingButton:{
                    try{
                        Settings *setting = new Settings(m_window);
                        setting->run();
                    } catch (std::exception& e){
                        std::cout << e.what() << std::endl;
                        throw;
                    }
                    break;
                }
                case HelpButton:{
                    Help help = Help(m_window);
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