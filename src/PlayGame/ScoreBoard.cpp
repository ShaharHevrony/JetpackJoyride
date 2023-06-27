#include "PlayGame/ScoreBoard.h"
#include <cmath>

// Static member initialization
sf::Clock ScoreBoard::clock;
std::string ScoreBoard::time;
int ScoreBoard::score;
int ScoreBoard::best;

ScoreBoard::ScoreBoard() {
    // Constructor for the ScoreBoard class
    // Resets the clock and initializes score and best values
    clock.restart().asSeconds();
    score = 0;
    best = GameManager::instance().getBest();
}

ScoreBoard::~ScoreBoard() {
    // Destructor for the ScoreBoard class
}

void ScoreBoard::draw(sf::RenderWindow* window) {
    // Function to draw the score and time on the window
    // Sets the values for score, time, and best
    // Draws the score, time, and best on the window
    for (int i = 0; i < scoreBoard.size(); i++) {
        m_str[i].str("");
    }
    setTime();
    m_str[0] << score;
    m_str[1] << time;
    m_str[2] << best;

    for (int board = 0; board < scoreBoard.size(); board++) {
        m_scoreBoard[board] = sf::Text(scoreBoard[board] + m_str[board].str().c_str(),
            ResourcesManager::instance().getFont(), SCALE_SIZE);
        m_scoreBoard[board].setFillColor(sf::Color::White);
        m_scoreBoard[board].setPosition(SETTING_HEIGHT, SETTING_HEIGHT + SCALE_SIZE * board);
        window->draw(m_scoreBoard[board]);
    }
}

int ScoreBoard::getScore() const {
    // Function to retrieve the current score value
    return score;
}

void ScoreBoard::setScore() {
    // Function to reset the score value to 0
    score = 0;
}

void ScoreBoard::setTime() {
    // Function to set the current elapsed time
    // Updates the 'time' variable with the formatted time string
    if (PlayerStateManager::instance().getState() != DeadPlayer &&
        PlayerStateManager::instance().getState() != GameOver) {
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
    // Function to add points to the score
    // Updates the score value and updates the best score if necessary
    score += addToScore;
    if (best < score) {
        best = score;
    }
}
