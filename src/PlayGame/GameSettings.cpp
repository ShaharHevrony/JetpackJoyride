#include "GameSettings.h"

/**
 * Constructs a GameSettings object.
 * Initializes the GameSettings with the specified window.
 *
 * @param window The SFML RenderWindow to associate with the GameSettings.
 */
GameSettings::GameSettings(sf::RenderWindow& window) : m_window(&window) {
    create();
}

/**
 * Destructor for the GameSettings object.
 */
GameSettings::~GameSettings() {}

/**
 * Creates the game settings buttons and sets their properties.
 * Loads textures from the resource manager and sets the positions, origins, and scales of the buttons.
 */
void GameSettings::create() {
    // Set the background texture and scale it to fit the window
    m_background.setTexture(*ResourcesManager::instance().getFirstBackground());
    m_background.setScale(WINDOW_HEIGHT / m_background.getTexture()->getSize().y, WINDOW_HEIGHT / m_background.getTexture()->getSize().y);

    // Create game settings buttons
    for (int index = 0; index < GAME_SETTINGS; index++) {
        m_gameSettings[index].setTexture(*ResourcesManager::instance().getSettingButtons(index));
        m_gameSettings[index].setPosition(WIDTH_CENTER, PLAYER_POS_Y + DIV_TWO * GAME_SETTING_Y * index);
        m_gameSettings[index].setOrigin(WIDTH_CENTER / BUTTON_NUM, HEIGHT_CENTER / BUTTON_NUM);
        m_gameSettings[index].setOrigin(m_gameSettings[index].getTexture()->getSize().x / DIV_TWO, m_gameSettings[index].getTexture()->getSize().y / DIV_TWO);
        m_gameSettings[index].setScale(OBJECT_SCALE * ONE_POINT_FIVE, OBJECT_SCALE * ONE_POINT_FIVE); // Increase button size by 20%
    }
}

bool GameSettings::run(int playerType) {
    while (m_window->isOpen()) {
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            // Check if the window was closed
            if (event.type == sf::Event::Closed) {
                m_window->close();
                return false;
            }

            // Check if a mouse button was released
            if (event.type == sf::Event::MouseButtonReleased) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                // Check if the resume button was clicked and the player is not dead
                if (m_gameSettings[ZERO].getGlobalBounds().contains(mousePosF) && playerType != DeadPlayer) {
                    return false; // Resume the game
                }
                // Check if the restart button was clicked
                else if (m_gameSettings[FIRST].getGlobalBounds().contains(mousePosF)) {
                    return true; // Restart the game
                }
                // Check if the quit button was clicked
                else if (m_gameSettings[SECOND].getGlobalBounds().contains(mousePosF)) {
                    m_window->close();
                    return false; // Quit the game
                }
            }

            // Check if the mouse was moved
            if (event.type == sf::Event::MouseMoved) {
                for (int i = 0; i < settingsButtons.size(); i++) {
                    // Check if the mouse is over a settings button
                    if (m_gameSettings[i].getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                        m_gameSettings[i].setScale(OBJECT_SCALE * ONE_POINT_EIGHT, OBJECT_SCALE * ONE_POINT_EIGHT); // Increase button size by 20%
                    }
                    else {
                        m_gameSettings[i].setScale(OBJECT_SCALE * ONE_POINT_FIVE, OBJECT_SCALE * ONE_POINT_FIVE); // Reset button size
                    }
                }
            }
        }

        // Clear the window and draw the game settings elements
        m_window->clear();
        m_window->draw(m_background);

        // Draw the resume button if the player is not dead
        if (playerType != DeadPlayer && playerType != GameOver) {
            m_window->draw(m_gameSettings[ZERO]);
        }

        m_window->draw(m_gameSettings[FIRST]); // Draw the restart button
        m_window->draw(m_gameSettings[SECOND]); // Draw the quit button

        m_window->display(); // Update the window
    }
}
