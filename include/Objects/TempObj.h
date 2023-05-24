#pragma once
#include "Object.h"
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <filesystem>

class TempObj: public Object{
public:
    TempObj(sf::Texture* texture, const sf::Vector2f& position);
    ~TempObj();
    virtual void move(float time);
};

