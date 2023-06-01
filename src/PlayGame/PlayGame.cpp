#include <SFML/Graphics.hpp>
#include "PlayGame/PlayGame.h"

sf::Clock PlayGame::gameTime;

PlayGame::PlayGame(sf::RenderWindow &window) : m_window(&window) {
    m_world = std::make_unique<b2World>(b2Vec2(GRAVITATION_X, GRAVITATION_Y));
    sf::Vector2f playerPosition(PLAYER_POS_X, 700);
    m_tempPlayer = std::make_unique<Player>(ResourcesManager::instance().getPlayer(), playerPosition, &m_world);
    m_floor = std::make_unique<Bound>(&m_world, true);
    m_ceiling = std::make_unique<Bound>(&m_world, false); 
}

PlayGame::~PlayGame() {}

void PlayGame::create() {
    m_isDead = false;
    m_control.RandomCount_t.clear();

    createObjectMap();
    m_board.setFirstBackground();
    m_board.setBackgrounds(BACKGROUND);
}

void PlayGame::createObjectMap() {
    int random = randMap();
    sf::Vector2f position;
    //int random = 7;
    for (int row = 0; row < m_board.getMap(random).size(); row++) {
        for (int col = 0; col < NUM_OF_OBJECTS; col++) {
            char type = m_board.getMap(random)[row][col];
            position = sf::Vector2f(WINDOW_WIDTH + WINDOW_WIDTH/20 * row, START_POINT + WINDOW_WIDTH/20 * col);
            switch (type) {
                case COIN: {
                    m_singleObjects.push_back(std::make_unique<Coin>(ResourcesManager::instance().getCoin(), position));
                    if (lastObject == nullptr || position.x > lastObject->getObject().getPosition().x) {
                        lastObject = std::make_unique<Coin>(ResourcesManager::instance().getCoin(), position);
                    }
                    break;
                }
                case OBSTACLE: {
                    m_pairedObjects.push_back(std::make_unique<Obstacle>(ResourcesManager::instance().getObstacle(), position));
                    if (m_pairedObjects.size() % 2 == 0) {
                        m_pairedObjects[m_pairedObjects.size() - 2]->setPaired(position);
                        m_pairedObjects[m_pairedObjects.size() - 1]->setPaired(m_pairedObjects[m_pairedObjects.size() - 2]->getObject().getPosition());
                        if (lastObject == nullptr || position.x > lastObject->getObject().getPosition().x) {
                            lastObject = std::make_unique<Coin>(ResourcesManager::instance().getCoin(), position);
                        }
                        sf::Vector2f firstPosition = m_pairedObjects[m_pairedObjects.size() -2]->getObject().getPosition();
                        // Calculate the distance between the two positions
                        double distance = calculateDistance(firstPosition.x, firstPosition.y, position.x, position.y);

                        // Calculate the number of additional sprites needed to cover the distance
                        int additionalSprites = static_cast<int>(distance) - 1;

                        // Duplicate the sprite and set paired positions for the additional sprites
                        for (int i = 0; i < additionalSprites; ++i) {
                            sf::Vector2f newPosition = interpolatePosition(firstPosition, position,
                                                                   static_cast<float>(i + 1) / (additionalSprites + 1));
                            m_pairedObjects.push_back(
                                    std::make_unique<Obstacle>(ResourcesManager::instance().getLaserLine(),
                                                               newPosition));
                            m_pairedObjects[m_pairedObjects.size() - 1]->setPaired(newPosition);
                            }
                    }
                    break;
                }
                case SPACE: {
                    break;
                }
            }
        }
    }
}

void PlayGame::run() {
    create();
    bool spacePressed = false;
    while (m_window->isOpen()) {
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    m_window->close();
                    return;
                }
                case sf::Event::KeyPressed: {
                    if (event.key.code == sf::Keyboard::Space) {
                        spacePressed = true;
                        m_tempPlayer->setSpace(true);
                    }
                    break;
                }
                case sf::Event::KeyReleased: {
                    if (event.key.code == sf::Keyboard::Space) {
                        spacePressed = false;
                        m_tempPlayer->setSpace(false);
                    }
                    break;
                }
            }
        }
        if (lastObject->getObject().getPosition().x <= 0.f || lastObject == nullptr) {
            m_singleObjects.clear();
            m_pairedObjects.clear();
            createObjectMap();
        }
        moveObjects();
        if (spacePressed) {
            //here we check the pose of the player falling standing or lift
            m_tempPlayer->move(0);
        }
        else {
            m_tempPlayer->animate();
        }
        if (m_tempPlayer->getBody()->GetLinearVelocity().y > 0.0f && !spacePressed) {
            m_tempPlayer->move(0);
        }
        dealWithCollision();
        dealWithEvent();
        draw();
    }
}

void PlayGame::dealWithCollision() {
    //check if the player collision with coins
    for (auto &mySingleObj: m_singleObjects) {
        m_tempPlayer->handleCollision(*mySingleObj);
    }
    std::erase_if(m_singleObjects, [](const auto &item) { return item->getDelete(); });

    //check if the player collision with obstacles
    for (auto &myPeir: m_pairedObjects) {
        m_tempPlayer->handleCollision(*myPeir);
        if (myPeir->getCollided()) {
            m_isDead = true;
        }
    }
}

void PlayGame::dealWithEvent() {
    while (!EventsQueue::instance().empty()) {
        auto event = EventsQueue::instance().pop();
        switch (event.getEventType()) {
            case CollectedMoney: {
                //add sound of money here
                m_scoreBoard.addPoints(event.getPoints());
                break;
            }
            case Death: {
                sf::Sprite tempSpr;
                for (int index = 1; index < 2; index++) {
                    sf::Texture* tempTex = ResourcesManager::instance().getBarryDeath(index);
                    tempSpr.setTexture(*tempTex);
                    m_tempPlayer->setSprite(tempSpr);
                    m_tempPlayer->playAnimationOnce(tempTex);
                    m_tempPlayer->moveRightDown();
                }
                break;
            }
        }
    }
}

void PlayGame::draw() {
    m_window->clear();
    float changeInterval = 3.0f;
    // Calculate the elapsed time in seconds
    m_control.Time_t = m_control.LoopClock_t.getElapsedTime().asSeconds();
    float elapsedTime = m_control.Time_t;
    if (elapsedTime >= changeInterval) {
        m_control.Speed_t += 15.f;
        //elapsedTime -= changeInterval;
    }

    m_control.LoopClock_t.restart();
    m_board.moveBackgrounds(m_control.Time_t * m_control.Speed_t);
    for (int i = 0; i < BACKGROUND; ++i) {
        m_window->draw(m_board.getBackgrounds()[i]);
    }
    m_window->draw(m_board.getFirstBackground());

    for (int index = 0; index < m_pairedObjects.size(); index++) {
        if (index != m_pairedObjects.size() - 1 || m_pairedObjects.size() % 2 == 0) {
            m_pairedObjects[index]->draw(m_window);
        }
    }
    for (int row = 0; row < m_singleObjects.size(); row++) {
        m_singleObjects[row]->draw(m_window);
    }
    m_scoreBoard.draw(m_window);
    m_tempPlayer->draw(m_window);
    m_floor->draw(m_window);
    m_ceiling->draw(m_window);

    m_window->display();
}

void PlayGame::moveObjects() {
    float timeStep = TIME_STEP;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    m_world->Step(timeStep, velocityIterations, positionIterations);

    float time = gameTime.restart().asSeconds();
    lastObject->move(m_control.Time_t * m_control.Speed_t);
    for (int index = 0; index < m_pairedObjects.size(); index++) {
        if (index != m_pairedObjects.size() - 1 || m_pairedObjects.size() % 2 == 0) {
            m_pairedObjects[index]->animate();
            m_pairedObjects[index]->move(m_control.Time_t * m_control.Speed_t);
        }
    }

    for (int index = 0; index < m_singleObjects.size(); index++) {
        m_singleObjects[index]->animate();
        m_singleObjects[index]->move(m_control.Time_t * m_control.Speed_t);
    }
    /*
    if (m_isDead) {
        sf::Sprite tempSpr;
        for (int index = 0; index < 2; index++) {
            sf::Texture *tempTex = ResourcesManager::instance().getBarryDeath(index);
            tempSpr.setTexture(*tempTex);
            //m_player.setSprite(tempSpr);
            //m_player.playAnimationOnce(tempTex);
        }
    } else {
        //m_player.animate();
        //m_player.move(time);
    }*/
}

int PlayGame::randMap() {
    srand(time(nullptr));
    int random = rand() % MAP.size();
    if (m_control.RandomCount_t.size() != MAP.size()) {
        while (m_control.RandomCount_t.contains(random)) {
            random = rand() % MAP.size();
        }
        m_control.RandomCount_t.insert(random);
    } else {
        m_control.RandomCount_t.clear();
    }
    return random;
}

double PlayGame::calculateDistance(double x1, double y1, double x2, double y2) {
    double deltaX = x2 - x1;
    double deltaY = y2 - y1;
    double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    return distance;
}

sf::Vector2f PlayGame::interpolatePosition(const sf::Vector2f &position1, const sf::Vector2f &position2, float t) {
    float x = position1.x + t * (position2.x - position1.x);
    float y = position1.y + t * (position2.y - position1.y);
    return sf::Vector2f(x, y);
}