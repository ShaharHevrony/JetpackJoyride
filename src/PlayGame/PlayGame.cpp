#include <SFML/Graphics.hpp>
#include "PlayGame.h"

PlayGame::PlayGame(sf::RenderWindow &window) : m_window(&window) {
    m_world = new b2World(b2Vec2(GRAVITATION_X, GRAVITATION_Y));
    m_world->SetContactListener(&m_collisionBox2D);
    m_floor   = std::make_unique<Bound>(m_world, 1.f, FloorType);   //Create the floor of the game
    m_ceiling = std::make_unique<Bound>(m_world, 1.f, CeilingType); //Create the ceiling of the game

    sf::Vector2f playerPosition(PLAYER_POS_X, PLAYER_POS_Y);
    m_player  = std::make_unique<Player>(ResourcesManager::instance().getPlayer(), playerPosition, m_world, PlayerType);
    m_flame   = std::make_unique<Flame>(ResourcesManager::instance().getFlame(), playerPosition);

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
    m_settingButton.setScale(SET_OBJ_SCALE, SET_OBJ_SCALE);
}

void PlayGame::createObjectMap() {
    m_singleObjects.clear();
    m_pairedObjects.clear();
    
    //int random = randMap();
    sf::Vector2f position;
    int random = 0;
    for (int row = 0; row < m_board.getMap(random).size(); row++) {
        for (int col = 0; col < NUM_OF_OBJECTS; col++) {
            char type = m_board.getMap(random)[row][col];
            position = sf::Vector2f(WINDOW_WIDTH + OBJECT_MAP_POS * row, 5 * START_POINT + OBJECT_MAP_POS * col);
            switch (type) {
                case COIN: {
                    m_singleObjects.push_back(std::make_unique<Coin>(ResourcesManager::instance().getCoin(), position));
                    if (m_lastObject.x <= 0.f || position.x > m_lastObject.x) {
                        m_lastObject = position;
                    }
                    break;
                }
                case OBSTACLE: {
                    m_pairedObjects.push_back(std::make_unique<Obstacle>(ResourcesManager::instance().getObstacle(), position));
                    if (m_pairedObjects.size() % 2 == 0) {
                        sf::Vector2f otherPosition = m_pairedObjects[m_pairedObjects.size()-2]->getObject().getPosition();
                        m_pairedObjects[m_pairedObjects.size()-2]->setPaired(position);
                        m_pairedObjects[m_pairedObjects.size()-1]->setPaired(otherPosition);
                        if (m_lastObject.x <= 0.f || position.x > m_lastObject.x) {
                            m_lastObject = position;
                        }
                        float distance = m_pairedObjects[m_pairedObjects.size()-1]->calculateDistance();
                        float angle = m_pairedObjects[m_pairedObjects.size()-2]->calculateAngle();

                        m_singleObjects.push_back(std::make_unique<Beam>(ResourcesManager::instance().getLaserBeam(), position, angle));
                        m_singleObjects[m_singleObjects.size()-1]->getObject().setScale(1.f, distance/ResourcesManager::instance().getLaserBeam()->getSize().y);
                    }
                    break;
                }
                case MISSILE: {
                    position = sf::Vector2f(WINDOW_WIDTH+200, m_player->getObject().getPosition().x);
                    m_missile.push_back(std::make_unique<Missile>(ResourcesManager::instance().getMissile(0), position));
                    //Start the timer for the missile
                    m_missile[m_missile.size() - 1]->restartTime();
                    break;
                }
                case PIGGY: {
                    m_singleObjects.push_back(std::make_unique<Piggy>(ResourcesManager::instance().getPiggy(), position));
                    if (m_lastObject.x <= 0.f || position.x > m_lastObject.x) {
                        m_lastObject = position;
                    }
                    break;
                }
                case SCIENTIST: {
                    m_singleObjects.push_back(std::make_unique<Scientist>(ResourcesManager::instance().getScientist(), position));
                    m_singleObjects[m_singleObjects.size() - 1]->getObject().setScale(SET_OBJ_SCALE, SET_OBJ_SCALE);
                    sf::Vector2f pos = m_singleObjects[m_singleObjects.size() - 1]->getObject().getPosition();
                    m_singleObjects[m_singleObjects.size() - 1]->getObject().setPosition(position.x, PLAYER_POS_Y * 1.65);
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
}

void PlayGame::run() {
    create();
    bool alreadyDead = false;
    GameSettings setting = GameSettings(*m_window, m_board, m_control);
    bool restartGame = false;
    /*
    if (!m_music.openFromFile(PATH + "JetpackJoyrideMusic.wav")) {
        // Error loading music file
    }
        m_music.play();
        m_music.setLoop(true); // set the music to loop
    */
    while (m_window->isOpen() && !restartGame) {
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    m_window->close();
                    return;
                }
                case sf::Event::KeyPressed: {
                    if (event.key.code == sf::Keyboard::Space) {
                        m_player->setSpacePressed(true);
                        m_flame->setInUse(true);
                    }
                    break;
                }
                case sf::Event::KeyReleased: {
                    if (event.key.code == sf::Keyboard::Space) {
                        m_player->setSpacePressed(false);
                        m_flame->setInUse(false);
                    }
                    break;
                }
                //If the user clicks on the window
                case sf::Event::MouseButtonReleased: {
                    if (m_settingButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        restartGame = setting.run(m_player->getType());
                        m_control.LoopClock_t.restart();
                    }
                }
            }
        }
        if (m_lastObject.x <= 0.f) {
            createObjectMap();
        }
        if (m_lastCoin.x <= 0.f){
            m_fallingCoins.clear();
        }
        if (m_player->getType() == PlayerType || m_player->getType() == SuperPowerType) {
            moveObjects();
            if (m_player->getSpacePressed() || m_player->getBody()->GetLinearVelocity().y > 0.0f) {
                //Here we check the pose of the player falling standing or lift
                m_player->move(TIME_STEP);
            } else {
                m_player->animate();
            }
            dealWithCollision();
            dealWithEvent();
        } else if(m_player->getType() != SuperPowerType){
            deathMovement(alreadyDead);
            if (alreadyDead) {
                sf::Time elapsed = m_timer.getElapsedTime();
                if (elapsed.asSeconds() >= 2.0) {
                    restartGame = setting.run(m_player->getType());
                }
            }
        }
        draw();
    }
    //m_music.stop();

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
                //Add sound of money here
                m_scoreBoard.addPoints(event.getPoints());
                break;
            }
            case CollectedPiggy: {
                //Add sound of piggy here
                sf::Vector2f position = event.getPiggyPosition();
                float scale = 2.f;
                position.x += 20.f;
                for(int index = 0; index <= 40; index++){
                    scale += index/4;
                    position.x += scale;
                    m_fallingCoins.push_back(std::make_unique<Box2Coin>(ResourcesManager::instance().getCoin(), position, m_world, scale, FallingCoinType));
                    if(index == 40){
                        m_lastCoin = position;
                    }
                }
                break;
            }
            case startSuperPower: {
                //Add sound of money here
                //set screen to be slower
                //set life to 1 
                m_player->setObject(ResourcesManager::instance().getSuperPower(1), sf::Vector2u(2, 1), 0.18f);
                m_player->setType(SuperPowerType);
                break;
            }
            case ReturnRegular: {
                //Add sound of money here
                //set screen to be slower
                //set life to 1 
                m_player->setObject(ResourcesManager::instance().getPlayer(), sf::Vector2u(4, 1), 0.18f);
                m_player->setType(PlayerType);
                break;
            }
            case DeathInTheAir: {
                //Add sound of death here
                m_fallingCoins.clear();
                m_player->setObject(ResourcesManager::instance().getBarryDeath(0), sf::Vector2u(3, 1), 0.18f);
                b2Vec2 deathGravity(DEATH_GRAVITY_X, DEATH_GRAVITY_Y);
                m_world->SetGravity(deathGravity);
                m_floor->setChange(m_world);
                m_player->setChange(m_world);
                m_scoreBoard.setDead();
                break;
            }
            case DeadOnTheGround: {
                m_player->setObject(ResourcesManager::instance().getBarryDeath(1), sf::Vector2u(1, 2), 0.18f);
                //Rotate the player to lay on the floor
                b2Body* playerBody = m_player->getBody();
                playerBody->SetTransform(playerBody->GetPosition(), 0.5f * b2_pi); //Set rotation to 90 degrees
                m_player->getObject().setOrigin(-50, PLAYER_POS_Y/3);
                m_player->setType(GameOverType);
                break;
            }
        }
    }
}

void PlayGame::draw() {
    m_window->clear();
    m_board.draw(m_window, m_control, m_player->getType());

    for (int index = 0; index < m_singleObjects.size(); index++) {
        m_singleObjects[index]->draw(m_window);
    }
    for (int index = 0; index < m_pairedObjects.size(); index++) {
        if (index != m_pairedObjects.size() - 1 || m_pairedObjects.size() % 2 == 0) {
            m_pairedObjects[index]->draw(m_window);
        }
    }
    for (int index = 0; index < m_missile.size(); index++) {
        m_missile[index]->draw(m_window);
    }
    for (int index = 0; index < m_fallingCoins.size(); index++) {
        m_fallingCoins[index]->draw(m_window);
    }

    m_scoreBoard.draw(m_window);
    m_floor->draw(m_window);
    m_ceiling->draw(m_window);
    m_player->draw(m_window);
    if (m_flame->getInUse()) {
        m_flame->draw(m_window);
    }
    m_window->draw(m_settingButton);
    m_window->display();
}

void PlayGame::deathMovement(bool& alreadyDead) {
    m_flame->setInUse(false);
    float timeStep = 1.5 * TIME_STEP;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    m_world->Step(timeStep, velocityIterations, positionIterations);
    m_player->animate();

    float velocityDelta = 3/WINDOW_HEIGHT;
    if(std::abs(m_player->getBody()->GetLinearVelocity().x) <= velocityDelta
    && std::abs(m_player->getBody()->GetLinearVelocity().y) <= velocityDelta && !alreadyDead){
        alreadyDead = true;
        Event event = Event(DeadOnTheGround);
        EventsQueue::instance().push(event);
        dealWithEvent();
        m_timer.restart();
    }
}

void PlayGame::moveObjects() {
    sf::Vector2f lastPosition = sf::Vector2f(0.f,0.f);

    float timeStep = TIME_STEP;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    m_world->Step(timeStep, velocityIterations, positionIterations);

    for (int index = 0; index < m_pairedObjects.size(); index++) {
        if (index != m_pairedObjects.size() - 1 || m_pairedObjects.size() % 2 == 0) {
            m_pairedObjects[index]->move(m_control.Time_t * m_control.Speed_t);
            if (lastPosition.x <= 0.f || m_pairedObjects[index]->getObject().getPosition().x > lastPosition.x) {
                lastPosition = m_pairedObjects[index]->getObject().getPosition();
            }
        }
    }
    for (int index = 0; index < m_singleObjects.size(); index++) {
        m_singleObjects[index]->move(m_control.Time_t * m_control.Speed_t);
        if (lastPosition.x <= 0.f || m_singleObjects[index]->getObject().getPosition().x > lastPosition.x) {
            lastPosition = m_singleObjects[index]->getObject().getPosition();
        }
    }

    for (int index = 0; index < m_fallingCoins.size(); index++) {
        m_fallingCoins[index]->move(m_control.Time_t * m_control.Speed_t);
    }
    m_lastObject = lastPosition;

    if(m_flame->getInUse()){
        sf::Vector2f playerPosition = m_player->getObject().getPosition();
        sf::Vector2u playerSize = m_player->getObject().getTexture()->getSize();
        m_flame->setPlayerPos(sf::Vector2f(playerPosition.x + 10, playerPosition.y + (playerSize.y * SET_OBJ_SCALE) - 10));
        m_flame->move(TIME_STEP);
    }
    if (!m_missile.empty()) {
        for (int index = 0; index < m_missile.size(); index++) {
            if (m_missile[index]->getTime().getElapsedTime().asSeconds() <= 3) {
                m_missile[index]->move(m_control.Time_t * m_control.Speed_t);
                m_missile[index]->getObject().setPosition(WINDOW_WIDTH - 100, m_player->getObject().getPosition().y + (index * 90));
                m_missile[index]->setCurrPositionX(m_player->getObject().getPosition().y + (index * 90));
            } else if (m_missile[index]->getTime().getElapsedTime().asSeconds() >= 3 &&
                      m_missile[index]->getTime().getElapsedTime().asSeconds() < 5) {
                m_missile[index]->setObject(ResourcesManager::instance().getMissile(1), sf::Vector2u(2, 1), 0.18f);
                m_missile[index]->move(m_control.Time_t * m_control.Speed_t);
            } else if (m_missile[index]->getTime().getElapsedTime().asSeconds() >= 5) {
                m_missile[index]->move(m_control.Time_t * m_control.Speed_t);
                m_missile[index]->setObject(ResourcesManager::instance().getMissile(2), sf::Vector2u(7, 1), 0.18f);
                m_missile[index]->getObject().setPosition(m_missile[0]->getObject().getPosition().x - 1, m_missile[index]->getCurrPositionX());                
            }
            m_missile[index]->updateCollisionTime(timeStep);
        }
        for (int index = 0; index < m_missile.size(); index++) {
            if (m_missile[index]->getObject().getPosition().x < -100) {
                m_missile.erase(m_missile.begin() + index);
                index--; //Decrement the index since the vector size has decreased
            }

        }
    }
}

int PlayGame::randMap() {
    srand(time(nullptr));
    //int random = rand() % MAP.size();
    int random = 1;
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