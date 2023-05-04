#pragma once
#include <SFML/Graphics.hpp>

#include "Values.h"

class Controller {
public:
    Controller();
    ~Controller();
    void run();
    void create();

private:
    sf::RenderWindow m_window;
};
