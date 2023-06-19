#include "Help.h"

Help::Help(sf::RenderWindow& window) : m_window(&window) {}

Help::~Help() {}


void Help::create() {
    for(int index = 0; index < BACKGROUND; index++) {
        sf::Sprite tempHelp;
        tempHelp.setTexture(*ResourcesManager::instance().getHelp(index));
        tempHelp.setScale(WINDOW_WIDTH/tempHelp.getTexture()->getSize().x,  WINDOW_HEIGHT/tempHelp.getTexture()->getSize().y);
        m_helpBoard.push_back(tempHelp);
    }
    m_backButton.setPosition(WINDOW_WIDTH / 10, WINDOW_HEIGHT / 8);
    m_backButton.setTexture(*ResourcesManager::instance().getQuitKey());
    m_backButton.setOrigin(m_backButton.getTexture()->getSize().x / 2, m_backButton.getTexture()->getSize().y / 2);

    m_rightArrow.setTexture(*ResourcesManager::instance().getWiteArrow());
    m_leftArrow.setTexture(*ResourcesManager::instance().getWiteArrow());

    float arrowYPosition = WINDOW_HEIGHT / 1.18;

    sf::Vector2f leftArrowPosition(WINDOW_WIDTH - 300 * OBJECT_SCALE, arrowYPosition);
    sf::Vector2f rightArrowPosition(WINDOW_WIDTH - 150 * OBJECT_SCALE, arrowYPosition);

    // Set the positions and textures of the arrows
    m_rightArrow.setOrigin(m_rightArrow.getTexture()->getSize().x / 2, m_rightArrow.getTexture()->getSize().y / 2);
    m_leftArrow.setOrigin(m_leftArrow.getTexture()->getSize().x / 2, m_leftArrow.getTexture()->getSize().y / 2);
    m_leftArrow.setRotation(180);
    m_leftArrow.setPosition(leftArrowPosition);
    m_leftArrow.setScale(PLAYER_SCALE / 5, PLAYER_SCALE / 5);
    m_rightArrow.setPosition(rightArrowPosition);
    m_rightArrow.setScale(PLAYER_SCALE / 5, PLAYER_SCALE / 5);
}

void Help::run() {
    create();
    while (m_window->isOpen()) {
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed: {
                m_window->close();
                return;
            }
                                  //if the user clicks on the window
            case sf::Event::MouseButtonReleased: {
                if (m_backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    return;
                }
                if (m_leftArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) && m_helpNum != 0 ) {
                    m_helpNum--;
                    break;
                }
                if (m_rightArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) && m_helpNum != 2) {
                    m_helpNum++;
                    break;
                }
            }
            case sf::Event::MouseMoved: {
                if (m_leftArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                    m_leftArrow.setScale(PLAYER_SCALE / 3, PLAYER_SCALE/3); // Increase left arrow size by 20%
                    m_rightArrow.setScale(PLAYER_SCALE / 5, PLAYER_SCALE / 5); // Reset right arrow size
                }
                else if (m_rightArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                    m_rightArrow.setScale(PLAYER_SCALE/3, PLAYER_SCALE/3); // Increase right arrow size by 20%
                    m_leftArrow.setScale(PLAYER_SCALE / 5, PLAYER_SCALE / 5); // Reset left arrow size

                }
                else {
                    m_leftArrow.setScale(PLAYER_SCALE / 5, PLAYER_SCALE / 5); // Reset left arrow size
                    m_rightArrow.setScale(PLAYER_SCALE / 5, PLAYER_SCALE / 5); // Reset right arrow size
                }
                if (m_backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                    m_backButton.setScale(1.2, 1.2);
                }
                else {
                    m_backButton.setScale(1, 1);
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
