#include "ScoreBoard.h"

sf::Clock ScoreBoard::timer;
int ScoreBoard::score;
int ScoreBoard::best;

ScoreBoard::ScoreBoard() {
    for(int bar = 0; bar < 3; bar++){
        m_text[bar] = sf::Text(scoreBoard[bar], ResourcesManager::instance().getFont(), 20);
    }
    timer.restart().asSeconds();
}

ScoreBoard::~ScoreBoard() {}

void ScoreBoard::draw(sf::RenderWindow &window) {
    float elapse = round(timer.getElapsedTime().asSeconds());
    std::stringstream str[3];
    for (int i = 0; i < 4; i++){
        str[i].str("");
    }
    str[0] << score;
    str[1] << elapse;
    str[2] << best;

    for(int board = 0; board < 3; board++){
        m_scoreBoard[board] = sf::Text(m_text[board].getString() + str[board].str().c_str(), ResourcesManager::instance().getFont(),50);
        m_scoreBoard[board].setFillColor(sf::Color::White);
        m_scoreBoard[board].setPosition(30, 40 + 50 * board);
        window.draw(m_scoreBoard[board]);
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