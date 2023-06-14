#include "Shop.h"

Shop::Shop(sf::RenderWindow& window): m_window(&window) {}

Shop::~Shop() {}

void Shop::create() {
    //create shop
    m_shopBoard.setTexture(*ResourcesManager::instance().getGameMenu());
    m_shopBoard.setScale(WINDOW_WIDTH / m_shopBoard.getTexture()->getSize().x, WINDOW_HEIGHT / m_shopBoard.getTexture()->getSize().y);
    m_backButton.setPosition(WINDOW_WIDTH / 10, WINDOW_HEIGHT / 8);
    m_backButton.setTexture(*ResourcesManager::instance().getQuitKey());

    // Define the horizontal and vertical spacing between squares
    float horizontalSpacing = 100;
    float verticalSpacing   = 100;

    for (int board = 0; board < 4; board++) {
        // Calculate the row and column of the current square
        int row = board / 2;
        int col = board % 2;

        // Calculate the position of the current square
        sf::Vector2f position(WINDOW_WIDTH/3 + (col * (PLAYER_POS_X + horizontalSpacing)), WINDOW_HEIGHT/8 + (row * (PLAYER_POS_Y + verticalSpacing)));

        // Draw the rectangle
        sf::RectangleShape tempRec(sf::Vector2f(PLAYER_POS_X, PLAYER_POS_Y));
        tempRec.setPosition(position);
        tempRec.setFillColor(sf::Color::White);
        m_characters.push_back(tempRec);
        m_window->draw(m_characters[board]);

        // Draw the name under the rectangle
        sf::Text tempName(squareNames[board], ResourcesManager::instance().getFont(), SCALE_SIZE);
        tempName.setFillColor(sf::Color::White);
        tempName.setPosition(position.x + (m_characters[board].getSize().x / 2) - (tempName.getLocalBounds().width / 2), position.y + m_characters[board].getSize().y + 20);  //Increase the vertical offset
        m_names.push_back(tempName);
        m_window->draw(m_names[board]);
    }
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

void Shop::move() {}

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
    m_window->display();
}
