#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "Values.h"
#include "ResourcesManager.h"

class ScoreBoard {
public:
    ScoreBoard();
    ~ScoreBoard();
    void draw(sf::RenderWindow *window);
    int getScore() const;
    void addPoints(int addToScore);
    int getBest() const;
    void setBest(int newBest);
    void setDead();

    static sf::Clock timer;
    static int score;
    static int best;

private:
    bool m_dead = false;
    float m_lastTime;
    std::stringstream m_str[3];
    sf::Text m_scoreBoard[3];
};
