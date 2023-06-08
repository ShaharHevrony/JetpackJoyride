#include "Shop.h"

Shop::Shop(sf::RenderWindow& window): m_window(&window) {}

Shop::~Shop() {}

void Shop::create() {
    m_overlay = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

    m_shopWindow.setSize(sf::Vector2f(SETTING_WIDTH ,SETTING_HEIGHT));
    m_shopWindow.setPosition(WIDTH_CENTER, HEIGHT_CENTER);
    m_shopWindow.setOrigin(SETTING_WIDTH/2, SETTING_HEIGHT/2);
    m_shopWindow.setFillColor(sf::Color(150,150,150));
}

void Shop::run(GameControllerInfo& gameController) {
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
        draw(gameController);
    }
}

void Shop::move() {}

void Shop::draw(GameControllerInfo &gameController) {
    m_overlay.setFillColor(sf::Color(0, 0, 0, 128));  // Semi-transparent black overlay
    m_window->draw(m_overlay);
    m_window->draw(m_shopWindow);
    m_window->display();
}

