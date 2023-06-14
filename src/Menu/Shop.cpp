#include "Shop.h"

Shop::Shop(sf::RenderWindow& window): m_window(&window) {}

Shop::~Shop() {}

void Shop::create() {
    //create shop
    m_shopBoard.setTexture(*ResourcesManager::instance().getGameMenu());
    m_shopBoard.setScale(WINDOW_WIDTH / m_shopBoard.getTexture()->getSize().x, WINDOW_HEIGHT / m_shopBoard.getTexture()->getSize().y);
    m_backButton.setPosition(WINDOW_WIDTH / 10, WINDOW_HEIGHT / 8);
    m_backButton.setTexture(*ResourcesManager::instance().getQuitKey());

    // Define the size and position of the big rectangle
    sf::Vector2f rectSize(PLAYER_POS_X * 2 + 100, PLAYER_POS_Y * 2 + 100);
    sf::Vector2f rectPosition((WINDOW_WIDTH - rectSize.x) / 2, (WINDOW_HEIGHT - rectSize.y) / 2);

    // Draw the big rectangle
    sf::RectangleShape tempRec(rectSize);
    tempRec.setPosition(rectPosition);
    tempRec.setFillColor(sf::Color::White);
    m_characters.push_back(tempRec);
    m_window->draw(m_characters[0]);

    // Draw the name under the rectangle
    sf::Text tempName(squareNames[0], ResourcesManager::instance().getFont(), SCALE_SIZE);
    tempName.setFillColor(sf::Color::White);
    tempName.setPosition(rectPosition.x + (rectSize.x / 2) - (tempName.getLocalBounds().width / 2), rectPosition.y + rectSize.y + 20);  //Increase the vertical offset
    m_names.push_back(tempName);

    m_rightArrow.setTexture(*ResourcesManager::instance().getArrow());
    m_leftArrow.setTexture(*ResourcesManager::instance().getArrow());

    float arrowYPosition = rectPosition.y + (rectSize.y / 2);

    sf::Vector2f leftArrowPosition(rectPosition.x - 100*OBJECT_SCALE, arrowYPosition);
    sf::Vector2f rightArrowPosition(rectPosition.x + rectSize.x + 100*OBJECT_SCALE, arrowYPosition);

    // Set the positions and textures of the arrows
    m_rightArrow.setOrigin(m_rightArrow.getTexture()->getSize().x / 2, m_rightArrow.getTexture()->getSize().y / 2);
    m_leftArrow.setOrigin(m_leftArrow.getTexture()->getSize().x / 2, m_leftArrow.getTexture()->getSize().y / 2);
    m_rightArrow.setRotation(180);
    m_leftArrow.setPosition(leftArrowPosition);
    m_rightArrow.setPosition(rightArrowPosition);
}


void Shop::run() {
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
                    if(m_backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
                        return;
                    }
                }
                case sf::Event::MouseMoved: {
                    //handleMouseMoved(event.mouseMove);
                    break;
                }
            }
        }
        draw();
    }
}


void Shop::draw() {
    m_window->clear();
    m_window->draw(m_shopBoard);
    for(int index = 0; index < m_characters.size(); index++) {
        m_window->draw(m_characters[index]);
        m_window->draw(m_names[index]);
    }
    auto collectedSum = GameManager::instance().getCollectedSum();
    // Draw the money text
    sf::Text money("you have: " + std::to_string(collectedSum), ResourcesManager::instance().getFont(), SCALE_SIZE);
    money.setPosition(SHOP_POS_X, SHOP_POS_Y);
    m_window->draw(money);
    m_window->draw(m_backButton);
    m_window->draw(m_rightArrow);
    m_window->draw(m_leftArrow);
    m_window->display();
}
