#include "PlayGame/ScoreBoard.h"
#include <cmath>

sf::Clock ScoreBoard::timer;
int ScoreBoard::score;
int ScoreBoard::best;

ScoreBoard::ScoreBoard() {
    timer.restart().asSeconds();
}

ScoreBoard::~ScoreBoard() {}

void ScoreBoard::draw(sf::RenderWindow *window) {
    float elapse = round(timer.getElapsedTime().asSeconds());
    for (int i = 0; i < scoreBoard.size(); i++){
        m_str[i].str("");
    }
    m_str[0] << score;
    if (!m_dead) {
        m_str[1] << elapse;
        m_lastTime = elapse;
    }
    else {
        m_str[1] << m_lastTime;
    }
    m_str[2] << best;

    for(int board = 0; board < scoreBoard.size(); board++){
        m_scoreBoard[board] = sf::Text(scoreBoard[board] + m_str[board].str().c_str(), ResourcesManager::instance().getFont(), SETTING_SIZE);
        m_scoreBoard[board].setFillColor(sf::Color::White);
        m_scoreBoard[board].setPosition(START_POINT, START_POINT + SETTING_SIZE * board);
        window->draw(m_scoreBoard[board]);
    }
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
void ScoreBoard::setDead() {
    m_dead = true;
}