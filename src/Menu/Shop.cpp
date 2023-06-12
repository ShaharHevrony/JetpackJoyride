#include "Shop.h"

Shop::Shop(sf::RenderWindow& window): m_window(&window) {}

Shop::~Shop() {}

void Shop::create() {
    m_window->clear();
    //create shop
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
    //draw the shop
    m_window->display();
}

