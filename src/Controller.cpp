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
        create();
    }
}