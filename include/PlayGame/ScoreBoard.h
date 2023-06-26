#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "Values.h"
#include "ResourcesManager.h"
#include "PlayerStateManager.h"
#include "GameManager.h"

class ScoreBoard {
public:
    ScoreBoard();
    ~ScoreBoard();
    void draw(sf::RenderWindow *window);
    int getScore() const;
    void setScore();
    void setTime();
    void addPoints(int addToScore);
    //int getBest() const;
    //void setBest(int newBest);
    //void setDead();

private:
    static sf::Clock clock;
    static int score;
    static std::string time;
    static int best;

    std::stringstream m_str[3];
    sf::Text m_scoreBoard[3];
};
