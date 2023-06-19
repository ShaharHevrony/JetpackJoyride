#include "GameSettings.h"

GameSettings::GameSettings(sf::RenderWindow &window, Board& board, Control& control) :m_window(&window) , m_control(control) {
    create();
}

GameSettings::~GameSettings() {}

void GameSettings::create() {
    m_background.setTexture(*ResourcesManager::instance().getFirstBackground());
    m_background.setScale(WINDOW_HEIGHT/m_background.getTexture()->getSize().y, WINDOW_HEIGHT/m_background.getTexture()->getSize().y);


    for(int index = 0; index < GAME_SETTINGS; index++) {
        m_gameSettings[index].setTexture(*ResourcesManager::instance().getSettingButtons(index));
        m_gameSettings[index].setPosition(WIDTH_CENTER, HEIGHT_CENTER / 2 + SCALE_SIZE * index*OBJECT_SCALE*3);
        m_gameSettings[index].setOrigin(WIDTH_CENTER/8, HEIGHT_CENTER/8);
        m_gameSettings[index].setOrigin(m_gameSettings[index].getTexture()->getSize().x / 2, m_gameSettings[index].getTexture()->getSize().y / 2);
        m_gameSettings[index].setScale(OBJECT_SCALE * 1.5, OBJECT_SCALE * 1.5); //Increase button size by 20%
    }
}

bool GameSettings::run(int playerType) {
    while (m_window->isOpen()) {
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window->close();
                return false;
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                if(m_gameSettings[0].getGlobalBounds().contains(mousePosF) && playerType != DeadPlayer){
                    return false;      //Resume the game
                } else if (m_gameSettings[1].getGlobalBounds().contains(mousePosF)) {
                    return true;       //Restart the game
                }else if (m_gameSettings[2].getGlobalBounds().contains(mousePosF)) {
                    m_window->close();
                    return false;     //Quit the game
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                for (int i = 0; i < settingsButtons.size() ; i++) {
                    if (m_gameSettings[i].getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                        m_gameSettings[i].setScale(OBJECT_SCALE * 1.8, OBJECT_SCALE * 1.8); //Increase button size by 20%
                    }
                    else {
                        m_gameSettings[i].setScale(OBJECT_SCALE * 1.5, OBJECT_SCALE * 1.5); //Reset button size
                    }
                }
            }

        }
        m_window->clear();
        m_window->draw(m_background);
        if(playerType != DeadPlayer && playerType != GameOver) {
            m_window->draw(m_gameSettings[0]);
        }
        m_window->draw(m_gameSettings[1]);
        m_window->draw(m_gameSettings[2]);
        m_window->display();
    }
}
