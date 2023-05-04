#include "Controller.h"
#include "ResourcesManager.h"

Controller::Controller() :m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jetpack Joyride"){
    create();
}

Controller::~Controller() {}

void Controller::create() {
    sf::Sprite title;
    title = ResourcesManager::inctance().getTitle();
    m_window.draw(title);

    m_window.display();
}

void Controller::run() {
    while (m_window.isOpen()){
        create();
    }
}