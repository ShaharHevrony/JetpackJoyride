#include "PlayGame/ScoreBoard.h"
#include <cmath>

sf::Clock ScoreBoard::clock;
std::string ScoreBoard::time;
int ScoreBoard::score;
int ScoreBoard::best;

ScoreBoard::ScoreBoard() {
    clock.restart().asSeconds();
    score = 0;
    best = GameManager::instance().getBest();
}

ScoreBoard::~ScoreBoard() {}

void ScoreBoard::draw(sf::RenderWindow *window) {
    for (int i = 0; i < scoreBoard.size(); i++){
        m_str[i].str("");
    }
    setTime();
    m_str[0] << score;
    m_str[1] << time;
    m_str[2] << best;

    for(int board = 0; board < scoreBoard.size(); board++){
        m_scoreBoard[board] = sf::Text(scoreBoard[board] + m_str[board].str().c_str(), ResourcesManager::instance().getFont(), SCALE_SIZE);
        m_scoreBoard[board].setFillColor(sf::Color::White);
        m_scoreBoard[board].setPosition(SETTING_HEIGHT, SETTING_HEIGHT + SCALE_SIZE * board);
        window->draw(m_scoreBoard[board]);
    }
}

int ScoreBoard::getScore() const {
    return score;
}

void ScoreBoard::setScore() {
    score = 0;
}

void ScoreBoard::setTime() {
    if (PlayerStateManager::instance().getState() != DeadPlayer && PlayerStateManager::instance().getState() != GameOver) {
        int elapse = round(clock.getElapsedTime().asSeconds());
        int minute = 0;
        while (elapse >= MINUTE) {
            minute++;
            elapse -= MINUTE;
        }
        time = std::to_string(minute) + ":" + std::to_string(elapse);
    }
}

void ScoreBoard::addPoints(int addToScore) {
    score += addToScore;
    if(best < score) {
        best = score;
    }
}