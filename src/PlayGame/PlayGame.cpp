#include "PlayGame.h"

PlayGame::PlayGame(sf::RenderWindow &window) : m_window(&window) {
    m_world   = new b2World(b2Vec2(GRAVITATION_X, GRAVITATION_Y));
    m_world->SetContactListener(&m_collisionBox2D);
    m_floor   = std::make_unique<Bound>(m_world, B2Floor);   //the prob starts
    m_ceiling = std::make_unique<Bound>(m_world, B2Ceiling); //Create the ceiling of the game

    sf::Vector2f playerPosition(PLAYER_POS_X, PLAYER_POS_Y);
    m_player  = std::make_shared<Player>(ResourcesManager::instance().getPlayer(), playerPosition, m_world, B2Player);
    m_flame   = std::make_unique<Flame>(ResourcesManager::instance().getFlame(), playerPosition);
    PlayerStateManager::instance().setPlayer(m_player);
}

PlayGame::~PlayGame() {}

void PlayGame::create() {
    m_control.RandomCount_t.clear();
    createObjectMap();
    m_board.setFirstBackground();
    m_board.setBackgrounds(BACKGROUND);

    m_settingButton.setTexture(*ResourcesManager::instance().getGameSetting());
    m_settingButton.setPosition(GAME_SETTING_X, GAME_SETTING_Y);
    m_settingButton.setOrigin(m_settingButton.getTexture()->getSize().x/2, m_settingButton.getTexture()->getSize().y/2);
    m_settingButton.setScale(OBJECT_SCALE, OBJECT_SCALE);
}

void PlayGame::createObjectMap() {
    m_singleObjects.clear();
    m_pairedObjects.clear();
    
    int random = randMap();
    sf::Vector2f position = sf::Vector2f(GAME_SETTING_X, GAME_SETTING_Y);
    for (int row = 0; row < m_board.getMap(random).size(); row++) {
        for (int col = 0; col < NUM_OF_OBJECTS; col++) {
            char type = m_board.getMap(random)[row][col];
            position = sf::Vector2f(WINDOW_WIDTH + SCALE_SIZE * row, CEILING_POS_Y + SCALE_SIZE * col);
            switch (type) {
                case COIN: {
                    m_singleObjects.push_back(std::make_unique<Coin>(ResourcesManager::instance().getCoin(), position, m_world, 1.f, B2StaticCoin));
                    if (m_lastObject.x <= 0.f || position.x > m_lastObject.x) {
                        m_lastObject = position;
                    }
                    break;
                }
                case LASER: {
                    m_pairedObjects.push_back(std::make_unique<Laser>(ResourcesManager::instance().getLowerZappers(), position));
                    if (m_pairedObjects.size() % 2 == 0) {
                        sf::Vector2f otherPosition = m_pairedObjects[m_pairedObjects.size()-2]->getObject().getPosition();
                        m_pairedObjects[m_pairedObjects.size()-1]->calculateAngle(otherPosition);
                        if (m_lastObject.x <= 0.f || position.x > m_lastObject.x) {
                            m_lastObject = position;
                        }
                        float distance = m_pairedObjects[m_pairedObjects.size()-2]->calculateDistance(position);
                        float angle    = m_pairedObjects[m_pairedObjects.size()-2]->calculateAngle(position);
                        m_singleObjects.push_back(std::make_unique<Beam>(ResourcesManager::instance().getZappersBeam(), position, angle, distance));
                        m_singleObjects[m_singleObjects.size()-1]->getObject().setScale(1.f, distance/ResourcesManager::instance().getZappersBeam()->getSize().y);
                    }
                    break;
                }
                case MISSILE: {
                    position = sf::Vector2f(WINDOW_WIDTH+200, m_player->getObject().getPosition().x);
                    m_missile.push_back(std::make_unique<Missile>(ResourcesManager::instance().getMissile(0), position));
                    break;
                }
                case PIGGY: {
                    m_singleObjects.push_back(std::make_unique<Piggy>(ResourcesManager::instance().getPiggy(), position));
                    if (m_lastObject.x <= 0.f || position.x > m_lastObject.x) {
                        m_lastObject = position;
                    }
                    break;
                }
                case SUPERPOWER: {
                    m_singleObjects.push_back(std::make_unique<SuperPower>(ResourcesManager::instance().getSuperPower(0), position));
                    if (m_lastObject.x <= 0.f || position.x > m_lastObject.x) {
                        m_lastObject = position;
                    }
                    break;
                }
                case SPACE: {
                    break;
                }
            }
        }
    }
    createNonCollisionObjects();
}

void PlayGame::createNonCollisionObjects() { //FIXME: move to the board class and handle there.
    m_nonCollision.clear();
    //Create the player's flame:
    sf::Vector2f position;
    int numOfLights = (m_lastObject.x / WIDTH_CENTER) - 1;
    for (int light = 0; light < numOfLights; light++){
        position = sf::Vector2f(GAME_SETTING_X + light * WIDTH_CENTER, GAME_SETTING_Y);
        m_nonCollision.push_back(std::make_unique<Lights>(ResourcesManager::instance().getLights(), position));
        if (m_lastObject.x <= 0.f || position.x > m_lastObject.x) {
            m_lastObject = position;
        }
    }

    int numOfObj = (m_lastObject.x / HEIGHT_CENTER) - 1;
    for (int scientist = 0; scientist < numOfObj; scientist++){
        position = sf::Vector2f(GAME_SETTING_X + scientist * HEIGHT_CENTER, CEILING_POS_Y + SCALE_SIZE * NUM_OF_OBJECTS);
        m_nonCollision.push_back(std::make_unique<Scientist>(ResourcesManager::instance().getScientist(), position));
        if (m_lastObject.x <= 0.f || position.x > m_lastObject.x) {
            m_lastObject = position;
        }
    }
}

void PlayGame::run() {
    create();
    GameSettings setting = GameSettings(*m_window, m_board, m_control);
    bool restartGame = false;
    static sf::Clock speedIncreaseTimer;
    while (m_window->isOpen() && !restartGame) {
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    m_window->close();
                    return;
                }
                case sf::Event::KeyPressed: {
                    if (event.key.code == sf::Keyboard::Space) {
                        PlayerStateManager::instance().setSpacePressed(true);
                        if (PlayerStateManager::instance().getState() == Regular) {
                            m_flame->setInUse(true);
                        }
                    }
                    break;
                }
                case sf::Event::KeyReleased: {
                    if (event.key.code == sf::Keyboard::Space) {
                        PlayerStateManager::instance().setSpacePressed(false);
                        m_flame->setInUse(false);
                    }
                    break;
                }
                //If the user clicks on the window
                case sf::Event::MouseButtonReleased: {
                    if (m_settingButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        GameManager::instance().checkPotentialBest(m_scoreBoard.getScore());
                        restartGame = setting.run(PlayerStateManager::instance().getState());
                        m_control.LoopClock_t.restart();
                        m_scoreBoard.setScore();
                    }
                }
            }
        }
        //Increase speed every 5 seconds
        if (speedIncreaseTimer.getElapsedTime().asSeconds() >= 5.0f) {
            m_control.Speed_t += 50.9f;
            speedIncreaseTimer.restart();
        }
        if (m_lastObject.x <= 0.f) {
            createObjectMap();
        }
        if (m_lastCoin.x <= 0.f) {
            m_fallingCoins.clear();
        }
        if (PlayerStateManager::instance().getState() != DeadPlayer && PlayerStateManager::instance().getState() != GameOver) {
            moveObjects();
            dealWithCollision();
            dealWithEvent();
        } else {
            deathMovement();
            if (PlayerStateManager::instance().getState() == GameOver) {
                sf::Time elapsed = m_timer.getElapsedTime();
                if (elapsed.asSeconds() >= 2.0) {
                    GameManager::instance().checkPotentialBest(m_scoreBoard.getScore());
                    m_scoreBoard.setScore();
                    restartGame = setting.run(PlayerStateManager::instance().getState());
                }
            }
        }
        draw();
    }
    if (restartGame) {
        GameManager::instance().setCollectedSum(m_scoreBoard.getScore());
    }
}

void PlayGame::dealWithCollision() {
    //check if the player collision with coins
    float elapsed = m_collisionTimer.getElapsedTime().asSeconds();

    //check if the player collision with coins
    for (auto &mySingleObj: m_singleObjects) {
        m_player->handleCollision(*mySingleObj);
        mySingleObj->updateCollisionTime(elapsed);
    }
    std::erase_if(m_singleObjects, [](const auto &item) { return item->getDelete(); });
    m_collisionTimer.restart();

    //check if the player collision with box2Coins
    for (auto &myFallingCoin: m_fallingCoins) {
        m_player->handleCollision(*myFallingCoin);
        myFallingCoin->updateCollisionTime(elapsed);
    }
    std::erase_if(m_fallingCoins, [](const auto &item) { return item->getDelete(); });
    //check if the player collision with obstacles
    for (auto &myPair: m_pairedObjects) {
        m_player->handleCollision(*myPair);
    }

    //check if the player collision with missile
    for (auto &myMissile: m_missile) {
        m_player->handleCollision(*myMissile);
    }
    std::erase_if(m_missile, [](const auto& item) { return item->getDelete(); });
}

void PlayGame::dealWithEvent() {
    while (!EventsQueue::instance().empty()) {
        auto event = EventsQueue::instance().pop();
        switch (event.getEventType()) {
            case CollectedMoney: {
                m_scoreBoard.addPoints(event.getPoints());
                break;
            }
            case CollectedPiggy: {
                sf::Vector2f position = event.getPiggyPosition();
                int random;
                srand(time(nullptr));
                for(int index = 0; index <= 80; index++) {
                    position.x += index / 4;
                    random = (rand() % 10) + 1;
                    m_fallingCoins.push_back(std::make_unique<Coin>(ResourcesManager::instance().getCoin(), position, m_world, random, B2DynamicCoin));
                }
                m_lastCoin = m_fallingCoins[m_fallingCoins.size() - 1]->getObject().getPosition();
                break;
            }
            case startSuperPower: {
                if (!PlayerStateManager::instance().getIfSuperTank()) {
                    PlayerStateManager::instance().setState(SuperPowerTank, m_world);
                    PlayerStateManager::instance().setToSuperTank(true);
                }
                else {
                    PlayerStateManager::instance().setState(SuperPowerRunner, m_world);
                    PlayerStateManager::instance().setToSuperTank(false);
                }
                break;
            }
            case ReturnRegular: {
                PlayerStateManager::instance().setState(Regular, m_world);
                break;
            }
            case DeathInTheAir: {
                m_fallingCoins.clear();
                PlayerStateManager::instance().setState(DeadPlayer, m_world);
                m_scoreBoard.setDead();
                break;
            }
            case DeadOnTheGround: {
                PlayerStateManager::instance().setState(GameOver, m_world);
                break;
            }
        }
    }
}

void PlayGame::draw() {
    m_window->clear();
    m_floor->draw(m_window);
    m_ceiling->draw(m_window);
    m_board.draw(m_window, m_control, PlayerStateManager::instance().getState());

    for (auto &singleObj : m_singleObjects) {
        singleObj->draw(m_window);
    }
    for (auto &pairedObj : m_pairedObjects) {
        if (pairedObj != m_pairedObjects[m_pairedObjects.size() - 1] || m_pairedObjects.size() % 2 == 0) {
            pairedObj->draw(m_window);
        }
    }
    for (auto &missile : m_missile) {
        missile->draw(m_window);
    }
    for (auto &fallingCoin : m_fallingCoins) {
        fallingCoin->draw(m_window);
    }
    for (auto  &nonCollisionObj : m_nonCollision){
        nonCollisionObj->draw(m_window);
    }
    m_window->draw(m_settingButton);
    m_scoreBoard.draw(m_window);
    if (m_flame->getInUse()) {
        m_flame->draw(m_window);
    }
    m_player->draw(m_window);
    m_window->display();
}

void PlayGame::deathMovement() {
    m_flame->setInUse(false);
    float timeStep = 1.5 * TIME_STEP;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    m_world->Step(timeStep, velocityIterations, positionIterations);
    m_player->move(m_control.Time_t * m_control.Speed_t);

    float velocityDelta = 3/WINDOW_HEIGHT;
    if(std::abs(m_player->getBody()->GetLinearVelocity().x) <= velocityDelta
    && std::abs(m_player->getBody()->GetLinearVelocity().y) <= velocityDelta
    && PlayerStateManager::instance().getState() != GameOver && m_player->getObject().getPosition().y != CEILING_POS_Y) {
        Event event = Event(DeadOnTheGround);
        EventsQueue::instance().push(event);
        dealWithEvent();
        m_timer.restart();
    }
}

void PlayGame::moveObjects() {
    sf::Vector2f lastPosition = sf::Vector2f(0.f, 0.f);
    float timeStep = TIME_STEP;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    m_world->Step(timeStep, velocityIterations, positionIterations);
    m_player->move(m_control.Time_t * m_control.Speed_t);
    sf::Vector2f playerPosition = m_player->getObject().getPosition();
    sf::Vector2u playerSize = m_player->getObject().getTexture()->getSize();
    m_flame->setPlayerPos(sf::Vector2f(playerPosition.x + 10, playerPosition.y + (playerSize.y * OBJECT_SCALE) - 10));
    m_flame->move(m_control.Time_t * m_control.Speed_t);

    for (auto &pairedObj : m_pairedObjects) {
        if (pairedObj != m_pairedObjects[m_pairedObjects.size() - 1] || m_pairedObjects.size() % 2 == 0) {
            pairedObj->move(m_control.Time_t * m_control.Speed_t);
            if (lastPosition.x <= 0.f || pairedObj->getObject().getPosition().x > lastPosition.x) {
                lastPosition = pairedObj->getObject().getPosition();
            }
        }
    }
    for (auto &singleObj : m_singleObjects) {
        singleObj->move(m_control.Time_t * m_control.Speed_t);
        if (lastPosition.x <= 0.f || singleObj->getObject().getPosition().x > lastPosition.x) {
            lastPosition = singleObj->getObject().getPosition();
        }
    }
    m_lastObject = lastPosition;

    for (auto &fallingCoin : m_fallingCoins) {
        fallingCoin->move(m_control.Time_t * m_control.Speed_t);
    }
    for (auto &nonCollisionObj : m_nonCollision) {
        nonCollisionObj->move(m_control.Time_t * m_control.Speed_t);
    }
    for (int index = 0; index < m_missile.size(); index++) {
        m_missile[index]->changeByTime(m_control.Time_t, m_player->getObject().getPosition(), index);
        m_missile[index]->move(m_control.Time_t * m_control.Speed_t);
        if (m_missile[index]->getObject().getPosition().x < -100.f) {
            m_missile.erase(m_missile.begin() + index);
            index--; //Decrement the index since the vector size has decreased
        }
    }
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