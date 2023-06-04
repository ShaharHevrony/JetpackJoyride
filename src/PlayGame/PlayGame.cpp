#include <SFML/Graphics.hpp>
#include "PlayGame/PlayGame.h"

PlayGame::PlayGame(sf::RenderWindow &window) : m_window(&window) {
    sf::Vector2f playerPosition(PLAYER_POS_X+30, 500);

    m_world   = std::make_unique<b2World>(b2Vec2(GRAVITATION_X, GRAVITATION_Y));
    m_player  = std::make_unique<Player>(ResourcesManager::instance().getPlayer(), playerPosition, &m_world, PlayerType);
    m_floor   = std::make_unique<Bound>(&m_world, FloorType);  //Create the floor of the game
    m_ceiling = std::make_unique<Bound>(&m_world, CeilingType); //Create the ceiling of the game
    m_world->SetContactListener(&m_collisionBox2D);
}

PlayGame::~PlayGame() {}

void PlayGame::create() {
    m_control.RandomCount_t.clear();
    createObjectMap();
    m_board.setFirstBackground();
    m_board.setBackgrounds(BACKGROUND);
}

void PlayGame::createObjectMap() {
    //int random = randMap();
    sf::Vector2f position;
    int random = 7;
    for (int row = 0; row < m_board.getMap(random).size(); row++) {
        for (int col = 0; col < NUM_OF_OBJECTS; col++) {
            char type = m_board.getMap(random)[row][col];
            position = sf::Vector2f(WINDOW_WIDTH + OBJECT_MAP_POS * row, 5 * START_POINT + OBJECT_MAP_POS * col);
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
                        sf::Vector2f otherPosition = m_pairedObjects[m_pairedObjects.size()-2]->getObject().getPosition();
                        m_pairedObjects[m_pairedObjects.size()-2]->setPaired(position);
                        m_pairedObjects[m_pairedObjects.size()-1]->setPaired(otherPosition);
                        if (lastObject == nullptr || position.x > lastObject->getObject().getPosition().x) {
                            lastObject = std::make_unique<Coin>(ResourcesManager::instance().getCoin(), position);
                        }
                        createBeam(position);
                       //------------------------------------------------------------
                    }
                    break;
                }
                case SPACE: {
                    break;
                }
                case MISSILE: {
                    //position = sf::Vector2f(WINDOW_WIDTH+200, m_player->getObject().getPosition().x);
                    //m_singleObjects.push_back(std::make_unique<Missile>(ResourcesManager::instance().getMissile(0), position));

                    position = sf::Vector2f(WINDOW_WIDTH, m_player->getObject().getPosition().y);
                    auto missile = std::make_unique<Missile>(ResourcesManager::instance().getMissile(0), position);
                    m_singleObjects.insert(m_singleObjects.begin(), std::move(missile));
                    m_singleObjects[0]->setObject(ResourcesManager::instance().getMissile(0), sf::Vector2u(3, 1));


                    break;
                }
            }
        }
    }
}

void PlayGame::createBeam(sf::Vector2f position) {
    /*sf::Sprite tempBeams[3];
    for(int index = 0; index < 3; index++) {
        tempBeams[index].setTexture(*ResourcesManager::instance().getLaserBeam(index));
        tempBeams[index].setScale(SET_OBJ_SCALE, SET_OBJ_SCALE);
    }*/

    sf::Vector2f firstPosition = m_pairedObjects[m_pairedObjects.size() - 2]->getObject().getPosition();
    float distance = m_pairedObjects[m_pairedObjects.size() - 1]->calculateDistance();
    int additionalSprites = static_cast<int>(distance) - 1;

    for (int i = 0; i < additionalSprites; ++i) {
        sf::Vector2f newPosition = interpolatePosition(firstPosition, position, static_cast<float>(i + 1) / (additionalSprites + 1));
        //m_pairedObjects.push_back(std::make_unique<Obstacle>(ResourcesManager::instance().getLiserLine(), newPosition));
        m_pairedObjects[m_pairedObjects.size() - 1]->setPaired(newPosition);
    }
    
}

void PlayGame::run() {
    create();
    bool alreadyDead = false;

    while (m_window->isOpen() && !m_restartGame) {
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    m_window->close();
                    return;
                }
                case sf::Event::KeyPressed: {
                    if (event.key.code == sf::Keyboard::Space) {
                        m_player->setSpacePressed(true);
                    }
                    break;
                }
                case sf::Event::KeyReleased: {
                    if (event.key.code == sf::Keyboard::Space) {
                        m_player->setSpacePressed(false);
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
        if (m_player->getType() != DeadPlayerType) {
            moveObjects();
            if (m_player->getSpacePressed() || m_player->getBody()->GetLinearVelocity().y > 0.0f){
                //here we check the pose of the player falling standing or lift
                m_player->move(TIME_STEP);
            } else {
                m_player->animate();
            }
            dealWithCollision();
            dealWithEvent();
        }else {
            deathMovement(alreadyDead);
            if (alreadyDead && !m_gameOver) {
                // Start the timer when the player is dead and the game over screen is not displayed yet
                m_timer.restart();
                m_gameOver = true;
            }
        }
        if (m_gameOver) {
            // Check if 2 seconds have elapsed since the player's death
            sf::Time elapsed = m_timer.getElapsedTime();
            if (elapsed.asSeconds() >= 2.0) {
                // Display the game over screen and freeze the window
                displayGameOverScreen();
                continue;  // Skip the rest of the loop until the window is closed
            }
        }
        draw();
    }
}

void PlayGame::dealWithCollision() {
    //check if the player collision with coins
    for (auto &mySingleObj: m_singleObjects) {
        m_player->handleCollision(*mySingleObj);
    }
    std::erase_if(m_singleObjects, [](const auto &item) { return item->getDelete(); });

    //check if the player collision with obstacles
    for (auto &myPair: m_pairedObjects) {
        m_player->handleCollision(*myPair);
    }
}

void PlayGame::dealWithEvent() {
    while (!EventsQueue::instance().empty()) {
        auto event = EventsQueue::instance().pop();
        switch (event.getEventType()) {
            case CollectedMoney: {
                //Add sound of money here
                m_scoreBoard.addPoints(event.getPoints());
                break;
            }
            case DeathInTheAir: {
                //Add sound of death here
                m_player->setObject(ResourcesManager::instance().getBarryDeath(0), sf::Vector2u(3, 1));
                b2Vec2 deathGravity(DEATH_GRAVITY_X, DEATH_GRAVITY_Y);
                m_world.get()->SetGravity(deathGravity);
                m_floor->setDeath(m_world.get());
                m_player->setDeath(m_world.get());
                m_scoreBoard.setDead();
                //m_collisionBox2D.setContactCount(0);
               // m_scoreBoard.timer;
                break;
            }
            case DeadOnTheGround:{
                m_player->setObject(ResourcesManager::instance().getBarryDeath(1), sf::Vector2u(1, 2));

                // Rotate the player to lay on the floor
                b2Body* playerBody = m_player->getBody();
                playerBody->SetTransform(playerBody->GetPosition(), 0.5f * b2_pi); // Set rotation to 90 degrees
                m_player->getObject().setOrigin(-50, 150);
                break;
            }
        }
    }
}

void PlayGame::draw() {
    m_window->clear();
    m_board.draw(m_window, m_control, m_player->getType());

    for (int index = 0; index < m_pairedObjects.size(); index++) {
        if (index != m_pairedObjects.size() - 1 || m_pairedObjects.size() % 2 == 0) {
            m_pairedObjects[index]->draw(m_window);
        }
    }
    for (int index = 0; index < m_singleObjects.size(); index++) {
        m_singleObjects[index]->draw(m_window);
    }
    m_scoreBoard.draw(m_window);
    m_floor->draw(m_window);
    m_ceiling->draw(m_window);
    m_player->draw(m_window);

    m_window->display();
}

void PlayGame::deathMovement(bool& alreadyDead) {
    float timeStep = 1.5 * TIME_STEP;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    m_world->Step(timeStep, velocityIterations, positionIterations);
    m_player->animate();

    float velocityDelta = 3/WINDOW_HEIGHT;
    if(std::abs(m_player->getBody()->GetLinearVelocity().x) <= velocityDelta
    && std::abs(m_player->getBody()->GetLinearVelocity().y) <= velocityDelta && !alreadyDead){
        alreadyDead = true;
        Event event = Event(DeadOnTheGround, 0);
        EventsQueue::instance().push(event);
        dealWithEvent();
    }
}

void PlayGame::moveObjects() {
    float timeStep = TIME_STEP;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    m_world->Step(timeStep, velocityIterations, positionIterations);

    for (int index = 0; index < m_pairedObjects.size(); index++) {
        if (index != m_pairedObjects.size() - 1 || m_pairedObjects.size() % 2 == 0) {
            m_pairedObjects[index]->move(m_control.Time_t * m_control.Speed_t);
        }
    }
    for (int index = 0; index < m_singleObjects.size(); index++) {
        m_singleObjects[index]->move(m_control.Time_t * m_control.Speed_t);
    }
    lastObject->move(m_control.Time_t * m_control.Speed_t);

    m_singleObjects[0]->getObject().setPosition(WINDOW_WIDTH-100,m_player->getObject().getPosition().y);

}

int PlayGame::randMap() {
    srand(time(nullptr));
    //int random = rand() % MAP.size();
    int random = 7;
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

void PlayGame::displayGameOverScreen() {
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 128));  // Semi-transparent black overlay

    // Create the game over box
    sf::RectangleShape gameOverBox(sf::Vector2f(400, 200));
    gameOverBox.setFillColor(sf::Color(150,150,150));
    gameOverBox.setOutlineThickness(2);
    gameOverBox.setOutlineColor(sf::Color::Black);
    gameOverBox.setPosition((WINDOW_WIDTH - gameOverBox.getSize().x) / 2, (WINDOW_HEIGHT - gameOverBox.getSize().y) / 2);

    // Add text for options
    sf::Font font;
    if (!font.loadFromFile("Jetpackia.ttf")) {
        // Handle font loading error
    }

    sf::Text restartText;
    restartText.setFont(font);
    restartText.setCharacterSize(24);
    restartText.setFillColor(sf::Color::Black);
    restartText.setString("Restart");
    restartText.setPosition(gameOverBox.getPosition() + sf::Vector2f(20, 20));

    sf::Text quitText;
    quitText.setFont(font);
    quitText.setCharacterSize(24);
    quitText.setFillColor(sf::Color::Black);
    quitText.setString("Quit");
    quitText.setPosition(gameOverBox.getPosition() + sf::Vector2f(20, 80));

    while (m_window->isOpen()) {
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window->close();
                return;
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                if (restartText.getGlobalBounds().contains(mousePosF)) {
                    // Restart the game
                    m_restartGame = true;
                    return;
                }
                if (quitText.getGlobalBounds().contains(mousePosF)) {
                    // Quit the game
                    m_window->close();
                    return;
                }
            }
        }

        m_window->clear();

        // Draw the game over screen
        m_board.draw(m_window, m_control, m_player->getType());

        // Draw the overlay
        m_window->draw(overlay);

        // Draw the game over box and options
        m_window->draw(gameOverBox);
        m_window->draw(restartText);
        m_window->draw(quitText);

        // Display the window content
        m_window->display();
    }
}


