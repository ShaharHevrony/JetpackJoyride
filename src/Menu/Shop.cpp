#include "Shop.h"

Shop::Shop(sf::RenderWindow& window): m_window(&window) {}

Shop::~Shop() {}

void Shop::create() {
    //create shop
    m_shopeBoard.setTexture(*ResourcesManager::instance().getGameMenu());
    m_shopeBoard.setScale(WINDOW_WIDTH / m_shopeBoard.getTexture()->getSize().x, WINDOW_HEIGHT / m_shopeBoard.getTexture()->getSize().y);
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
                    //handleMouseButton(event.mouseButton);
                }
                case sf::Event::MouseMoved: {
                    //handleMouseMoved(event.mouseMove);
                }
            }
        }
        draw();
    }
}

void Shop::move() {}

void Shop::draw() {

    m_window->clear();
    m_window->draw(m_shopeBoard);

    sf::Vector2f squareSize(300, 300);  // Increase the size of the squares
    sf::Vector2f squarePosition(WINDOW_WIDTH/3, WINDOW_HEIGHT/8);  // Adjust the initial position of the squares

    // Define the horizontal and vertical spacing between squares
    float horizontalSpacing = 100;
    float verticalSpacing = 100;

    for (int board = 0; board < 4; board++) {
        // Calculate the row and column of the current square
        int row = board / 2;
        int col = board % 2;

        // Calculate the position of the current square
        sf::Vector2f position(squarePosition.x + (col * (squareSize.x + horizontalSpacing)),
            squarePosition.y + (row * (squareSize.y + verticalSpacing)));

        // Draw the rectangle
        sf::RectangleShape square(squareSize);
        square.setPosition(position);
        square.setFillColor(sf::Color::White);
        m_window->draw(square);

        // Draw the name under the rectangle
        sf::Text name(squareNames[board], ResourcesManager::instance().getFont(), SCALE_SIZE);
        name.setFillColor(sf::Color::White);
        name.setPosition(position.x + (squareSize.x / 2) - (name.getLocalBounds().width / 2),
            position.y + squareSize.y + 20);  // Increase the vertical offset
        m_window->draw(name);
    }

    m_window->display();
}

