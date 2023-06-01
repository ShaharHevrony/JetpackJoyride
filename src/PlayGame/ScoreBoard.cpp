#include "PlayGame/ScoreBoard.h"

sf::Clock ScoreBoard::timer;
int ScoreBoard::score;
int ScoreBoard::best;

ScoreBoard::ScoreBoard() {
    timer.restart().asSeconds();
}

ScoreBoard::~ScoreBoard() {}

void ScoreBoard::draw(sf::RenderWindow *window) {
    float elapse = round(timer.getElapsedTime().asSeconds());
    for (int i = 0; i < 3; i++){
        m_str[i].str("");
    }
    m_str[0] << score;
    m_str[1] << elapse;
    m_str[2] << best;

    for(int board = 0; board < 3; board++){
        m_scoreBoard[board] = sf::Text(scoreBoard[board] + m_str[board].str().c_str(), ResourcesManager::instance().getFont(),50);
        m_scoreBoard[board].setFillColor(sf::Color::White);
        m_scoreBoard[board].setPosition(30, 40 + 50 * board);
        window->draw(m_scoreBoard[board]);
    }
}

int ScoreBoard::getScore() const {
    return score;
}

void ScoreBoard::addPoints(int addToScore) {
    score += addToScore;
    if(best < score) {
        best = score;
    }
}

int ScoreBoard::getBest() const {
    return best;
}