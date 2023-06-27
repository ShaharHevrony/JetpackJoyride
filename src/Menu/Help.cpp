#include "Help.h"

Help::Help(sf::RenderWindow& window) : m_window(&window) {}

Help::~Help() {}

void Help::create() {
    //Load help images and scale them to fit the window size
    for (int index = 0; index < BACKGROUND; index++) {
        sf::Sprite tempHelp;
        tempHelp.setTexture(*ResourcesManager::instance().getHelp(index));
        tempHelp.setScale(WINDOW_WIDTH / tempHelp.getTexture()->getSize().x, WINDOW_HEIGHT / tempHelp.getTexture()->getSize().y);
        m_helpBoard.push_back(tempHelp);
    }

    //Set the position and texture of the back button
    m_backButton.setTexture(*ResourcesManager::instance().getQuitKey());
    m_backButton.setPosition(WINDOW_WIDTH/TEN, WINDOW_HEIGHT/EIGHTEEN);
    m_backButton.setOrigin(m_backButton.getTexture()->getSize().x/SECOND, m_backButton.getTexture()->getSize().y/SECOND);

    //Set the textures and positions of the arrows
    m_rightArrow.setTexture(*ResourcesManager::instance().getArrow());
    m_leftArrow.setTexture(*ResourcesManager::instance().getArrow());

    float arrowYPosition = WINDOW_HEIGHT / ONE_POINT_ONE_EIGHT;

    sf::Vector2f leftArrowPosition(WINDOW_WIDTH - THREE_HUNDRED * OBJECT_SCALE, arrowYPosition);
    sf::Vector2f rightArrowPosition(WINDOW_WIDTH - ONE_FIFTHY * OBJECT_SCALE, arrowYPosition);

    //Set the positions and scales of the arrows
    m_rightArrow.setOrigin(m_rightArrow.getTexture()->getSize().x / DIV_TWO, m_rightArrow.getTexture()->getSize().y / DIV_TWO);
    m_leftArrow.setOrigin(m_leftArrow.getTexture()->getSize().x / DIV_TWO, m_leftArrow.getTexture()->getSize().y / DIV_TWO);
    m_rightArrow.setRotation(ONE_EIGHTY);
    m_leftArrow.setPosition(leftArrowPosition);
    m_leftArrow.setScale(PLAYER_SCALE / FIVE_F, PLAYER_SCALE / FIVE_F);
    m_rightArrow.setPosition(rightArrowPosition);
    m_rightArrow.setScale(PLAYER_SCALE / FIVE_F, PLAYER_SCALE / FIVE_F);
}

void Help::run() {
    create();
    while (m_window->isOpen()) {
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed: {
                // Close the window when the "Closed" event is triggered
                m_window->close();
                return;
            }
            case sf::Event::MouseButtonReleased: {
                // Handle mouse button release events
                if (m_backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    // Return when the back button is clicked
                    return;
                }
                if (m_leftArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) && m_helpNum != ZERO) {
                    // Decrement help number when the left arrow is clicked and not at the first help page
                    m_helpNum--;
                    break;
                }
                if (m_rightArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) && m_helpNum != SECOND) {
                    // Increment help number when the right arrow is clicked and not at the last help page
                    m_helpNum++;
                    break;
                }
            }
            case sf::Event::MouseMoved: {
                // Handle mouse movement events
                if (m_leftArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                    // Increase left arrow size
                    m_leftArrow.setScale(PLAYER_SCALE / FOUR, PLAYER_SCALE/FOUR); // Increase left arrow size by 20%
                    m_rightArrow.setScale(PLAYER_SCALE / FIVE_F, PLAYER_SCALE / FIVE_F); // Reset right arrow size
                }
                else if (m_rightArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                    m_rightArrow.setScale(PLAYER_SCALE/ FOUR, PLAYER_SCALE/ FOUR); // Increase right arrow size by 20%
                    m_leftArrow.setScale(PLAYER_SCALE / FIVE_F, PLAYER_SCALE / FIVE_F); // Reset left arrow size

                } else {
                    m_leftArrow.setScale(PLAYER_SCALE / FIVE_F, PLAYER_SCALE / FIVE_F); // Reset left arrow size
                    m_rightArrow.setScale(PLAYER_SCALE / FIVE_F, PLAYER_SCALE / FIVE_F); // Reset right arrow size
                }
                if (m_backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                    m_backButton.setScale(ONE_POINT_TWO, ONE_POINT_TWO);
                }
                else {
                    m_backButton.setScale(FIRST, FIRST);
                }
                break;
            }
            }
        }
        draw();
    }
}


void Help::draw() {
    m_window->clear();
    m_window->draw(m_helpBoard[m_helpNum]);

    m_window->draw(m_backButton);
    m_window->draw(m_rightArrow);
    m_window->draw(m_leftArrow);
    m_window->display();
}
