
#include "GameSettings.h"

GameSettings::GameSettings(sf::RenderWindow &window, Board& board, Control& control)
            :m_window(&window) , m_control(control){
    create();
}

GameSettings::~GameSettings() {}

void GameSettings::create() {
    m_overlay.setTexture(*ResourcesManager::instance().getFirstBackground());
    m_overlay.setScale(WINDOW_HEIGHT/m_overlay.getTexture()->getSize().y, WINDOW_HEIGHT/m_overlay.getTexture()->getSize().y);
    //Create the game over box
    m_setting = sf::RectangleShape(sf::Vector2f(WIDTH_CENTER/2, HEIGHT_CENTER/2));
    m_setting.setFillColor(sf::Color(150,150,150));
    m_setting.setOutlineThickness(2);
    m_setting.setOutlineColor(sf::Color::Black);
    m_setting.setPosition(WIDTH_CENTER, HEIGHT_CENTER);
    m_setting.setOrigin(WIDTH_CENTER/4, HEIGHT_CENTER/4);

    for(int index = 0; index < GAME_SETTINGS; index++) {
        m_gameSettings[index] = sf::Text(gameSettings[index], ResourcesManager::instance().getFont(), SETTING_SIZE);
        m_gameSettings[index].setFillColor(sf::Color::Black);
        m_gameSettings[index].setPosition(m_setting.getPosition().x, m_setting.getPosition().y + SETTING_SIZE * index);
        m_gameSettings[index].setOrigin(WIDTH_CENTER/8, HEIGHT_CENTER/8);
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
                if(m_gameSettings[0].getGlobalBounds().contains(mousePosF) && playerType != DeadPlayerType){
                    return false;      //Resume the game
                } else if (m_gameSettings[1].getGlobalBounds().contains(mousePosF)) {
                    return true;       //Restart the game
                }else if (m_gameSettings[2].getGlobalBounds().contains(mousePosF)) {
                    m_window->close();
                    return false;      //Quit the game
                }
            }
        }
        m_window->clear();
        // Draw the game over screen
        // Draw the overlay
        m_window->draw(m_overlay);
        // Draw the game over box and options
        m_window->draw(m_setting);
        if(playerType != DeadPlayerType && playerType!= GameOverType) {
            m_window->draw(m_gameSettings[0]);
        }
        m_window->draw(m_gameSettings[1]);
        m_window->draw(m_gameSettings[2]);
        //Display the window content
        m_window->display();
    }
}
