#include "PlayGame.h"

PlayGame::PlayGame(sf::RenderWindow &window) : m_window(&window) {
    m_world   = new b2World(b2Vec2(GRAVITATION_X, GRAVITATION_Y));
    m_world->SetContactListener(&m_collisionBox2D);
    m_floor   = std::make_unique<Bound>(m_world, B2Floor);   //the prob starts
    m_ceiling = std::make_unique<Bound>(m_world, B2Ceiling); //Create the ceiling of the game

    sf::Vector2f playerPosition(PLAYER_POS_X, PLAYER_POS_Y);
    m_player  = std::make_shared<Player>(ResourcesManager::instance().getPlayerStates(GameManager::instance().getCharacter(), Regular), playerPosition, m_world, B2Player);
    m_flame   = std::make_unique<Flame>(ResourcesManager::instance().getFlame(), playerPosition);
    PlayerStateManager::instance().setPlayer(m_player);
}

PlayGame::~PlayGame() {}

void PlayGame::create() {
    createObjectMap();
    m_board.setFirstBackground();
    m_board.setBackgrounds(BACKGROUND);

    m_settingButton.setTexture(*ResourcesManager::instance().getGameSetting());
    m_settingButton.setPosition(GAME_SETTING_X, GAME_SETTING_Y);
    m_settingButton.setOrigin(m_settingButton.getTexture()->getSize().x/2, m_settingButton.getTexture()->getSize().y/2);
    m_settingButton.setScale(OBJECT_SCALE, OBJECT_SCALE);
}

void PlayGame::run() {
    create();
    GameSettings setting = GameSettings(*m_window);
    bool restartGame;
    sf::Time elapsed;
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
                        GameManager::instance().setCollectedSum(m_scoreBoard.getScore());
                        restartGame = setting.run(PlayerStateManager::instance().getState());
                        m_board.setClock();
                        m_scoreBoard.setScore();
                    }
                }
            }
        }
        if (restartGame) {
            GameManager::instance().setCollectedSum(m_scoreBoard.getScore());
        }
        checkIfNeedToClear();
        animateObj();
        if (PlayerStateManager::instance().getState() != DeadPlayer && PlayerStateManager::instance().getState() != GameOver) {
            moveObj();
            dealWithCollision();
            dealWithEvent();
        } else if (PlayerStateManager::instance().getState() == DeadPlayer) {
            deathMoveObj();
        } else {
            elapsed = m_timer.getElapsedTime();
            if (elapsed.asSeconds() >= 2.0) {
                GameManager::instance().checkPotentialBest(m_scoreBoard.getScore());
                GameManager::instance().setCollectedSum(m_scoreBoard.getScore());
                m_scoreBoard.setScore();
                restartGame = setting.run(PlayerStateManager::instance().getState());
            }
        }
        draw();
    }
}

void PlayGame::checkIfNeedToClear() {
    if (m_lastObject.x <= LAST_POSITION) {
        m_singleObj.clear();
        m_pairedObj.clear();
        m_missiles.clear();
        m_nonCollisionObj.clear();
        m_board.randMap();
        std::cout << "\n\n#### In clear ####\n\tFIRST num of missiles: " << m_missiles.size() << "\n";
        createObjectMap();
        createNonCollisionObj();
        std::cout << "\tFINAL num of missiles: " << m_missiles.size() << "\n";
    }
    //Delete objects that are out of range:
    for (auto &singleObj: m_singleObj) {
        if (singleObj->getObject().getPosition().x <= LAST_POSITION) {
            singleObj->setDelete();
        }
    }
    std::erase_if(m_singleObj, [](const auto &item) {return item->getDelete();});

    for (auto &fallingCoin: m_fallingCoins) {
        if (fallingCoin->getObject().getPosition().x <= LAST_POSITION) {
            fallingCoin->setDelete();
        }
    }
    std::erase_if(m_fallingCoins, [](const auto &item) {return item->getDelete();});

    for (auto &pair: m_pairedObj) {
        if (pair->getObject().getPosition().x <= LAST_POSITION) {
            pair->setDelete();
        }
    }
    std::erase_if(m_pairedObj, [](const auto& item) { return item->getDelete(); });

    for (auto &missile: m_missiles) {
        if (missile->getObject().getPosition().x <= LAST_POSITION) {
            missile->setDelete();
        }
    }
    std::erase_if(m_missiles, [](const auto& item) { return item->getDelete(); });

    for (auto &fallingCoins: m_fallingCoins) {
        if (fallingCoins->getObject().getPosition().x <= LAST_POSITION) {
            fallingCoins->setDelete();
        }
    }
    std::erase_if(m_fallingCoins, [](const auto& item) { return item->getDelete(); });
}

void PlayGame::createObjectMap() {
    sf::Vector2f position = sf::Vector2f(GAME_SETTING_X, GAME_SETTING_Y);
    m_lastObject.x = 0.f;
    for (int row = 0; row < m_board.getMap().size(); row++) {
        for (int col = 0; col < NUM_OF_OBJECTS; col++) {
            char type = m_board.getMap()[row][col];
            position = sf::Vector2f(WINDOW_WIDTH + SCALE_SIZE * row, CEILING_POS_Y + SCALE_SIZE * col);
            switch (type) {
                case COIN: {
                    m_singleObj.push_back(std::make_unique<Coin>(ResourcesManager::instance().getCoin(), position, m_world, 1.f, B2StaticCoin));
                    if (m_lastObject.x <= 0.f || position.x > m_lastObject.x) {
                        m_lastObject = position;
                    }
                    break;
                }
                case LASER: {
                    m_pairedObj.push_back(std::make_unique<Laser>(ResourcesManager::instance().getLowerZappers(), position));
                    if (m_pairedObj.size() % 2 == 0) {
                        sf::Vector2f otherPosition = m_pairedObj[m_pairedObj.size()-2]->getObject().getPosition();
                        m_pairedObj[m_pairedObj.size()-1]->calculateAngle(otherPosition);
                        if (position.x > m_lastObject.x) {
                            m_lastObject = position;
                        }
                        float distance = m_pairedObj[m_pairedObj.size()-2]->calculateDistance(position);
                        float angle    = m_pairedObj[m_pairedObj.size()-2]->calculateAngle(position);
                        m_singleObj.push_back(std::make_unique<Beam>(ResourcesManager::instance().getZappersBeam(), position, angle, distance));
                        m_singleObj[m_singleObj.size()-1]->getObject().setScale(OBJECT_SCALE, distance/ResourcesManager::instance().getZappersBeam()->getSize().y);
                    }
                    break;
                }
                case MISSILE: {
                    position = sf::Vector2f(WINDOW_WIDTH - 2*LAST_POSITION, m_player->getObject().getPosition().x);
                    m_missiles.push_back(std::make_unique<Missile>(ResourcesManager::instance().getMissile(0), position, m_missiles.size()));
                    if (position.x > m_lastObject.x) {
                        m_lastObject = position;
                    }
                    std::cout << "\tCURRENT num of missiles: " << m_missiles.size() << ". this missile's position is: ( " << position.x << " , " << position.y << " )\n";
                    break;
                }
                case PIGGY: {
                    m_singleObj.push_back(std::make_unique<Piggy>(ResourcesManager::instance().getPiggy(), position));
                    if (position.x > m_lastObject.x) {
                        m_lastObject = position;
                    }
                    break;
                }
                case SUPERPOWER: {
                    m_singleObj.push_back(std::make_unique<SuperPower>(ResourcesManager::instance().getSuperPower(Box), position));
                    if (position.x > m_lastObject.x) {
                        m_lastObject = position;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
}

void PlayGame::createNonCollisionObj() {
    //Create the player's flame:
    sf::Vector2f position;
    int numOfLights = (m_lastObject.x / WIDTH_CENTER) - 1;
    for (int light = 0; light < numOfLights; light++) {
        position = sf::Vector2f(GAME_SETTING_X + light * WIDTH_CENTER, GAME_SETTING_Y);
        m_nonCollisionObj.push_back(std::make_unique<Light>(ResourcesManager::instance().getLights(), position));
        if (position.x > m_lastObject.x) {
            m_lastObject = position;
        }
    }

    int numOfObj = (m_lastObject.x / HEIGHT_CENTER) - 1;
    for (int scientist = 0; scientist < numOfObj; scientist++) {
        position = sf::Vector2f(GAME_SETTING_X + scientist * HEIGHT_CENTER, WINDOW_HEIGHT/1.28);
        m_nonCollisionObj.push_back(std::make_unique<Scientist>(ResourcesManager::instance().getScientist(), position));
        if (position.x > m_lastObject.x) {
            m_lastObject = position;
        }
    }
}

void PlayGame::animateObj() {
    m_flame->animate();
    for (auto &pairedObj : m_pairedObj) {
        if (pairedObj != m_pairedObj[m_pairedObj.size() - 1] || m_pairedObj.size() % 2 == 0) {
            pairedObj->animate();
        }
    }
    for (auto &singleObj : m_singleObj) {
        singleObj->animate();
    }
    for (auto &fallingCoin : m_fallingCoins) {
        fallingCoin->animate();
    }
    for (auto &nonCollisionObj : m_nonCollisionObj) {
        nonCollisionObj->animate();
    }
    for (auto &missile: m_missiles) {
        missile->updateCollisionTime(m_board.getTime());
        missile->animate();
    }
}

void PlayGame::moveObj() {
    sf::Vector2f lastPosition = sf::Vector2f(0.f, 0.f);
    float timeStep = TIME_STEP;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    m_world->Step(timeStep, velocityIterations, positionIterations);

    m_board.moveBackgrounds();
    float movement = m_board.getMovement();
    m_player->move(movement);
    m_flame->move(movement);

    for (auto &pairedObj : m_pairedObj) {
        if (pairedObj != m_pairedObj[m_pairedObj.size() - 1] || m_pairedObj.size() % 2 == 0) {
            pairedObj->move(movement);
            if (lastPosition.x <= 0.f || pairedObj->getObject().getPosition().x > lastPosition.x) {
                lastPosition = pairedObj->getObject().getPosition();
            }
        }
    }
    for (auto &singleObj : m_singleObj) {
        singleObj->move(movement);
        if (lastPosition.x <= 0.f || singleObj->getObject().getPosition().x > lastPosition.x) {
            lastPosition = singleObj->getObject().getPosition();
        }
    }
    for (auto &missile: m_missiles) {
        missile->updateCollisionTime(m_board.getTime());
        missile->move(movement);
        if (lastPosition.x <= 0.f || missile->getObject().getPosition().x > lastPosition.x) {
            lastPosition = missile->getObject().getPosition();
        }
    }
    m_lastObject = lastPosition;

    for (auto &fallingCoin : m_fallingCoins) {
        fallingCoin->move(movement);
    }
    for (auto &nonCollision : m_nonCollisionObj) {
        nonCollision->move(movement);
    }
}

void PlayGame::deathMoveObj() {
    m_flame->setInUse(false);
    float timeStep = 1.5 * TIME_STEP;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    m_world->Step(timeStep, velocityIterations, positionIterations);
    m_player->move(m_board.getMovement());
    if(std::abs(m_player->getBody()->GetLinearVelocity().x) <= VELOCITY_DELTA
       && std::abs(m_player->getBody()->GetLinearVelocity().y) <= VELOCITY_DELTA
       && PlayerStateManager::instance().getState() != GameOver && m_player->getObject().getPosition().y > HEIGHT_CENTER) {
        Event event = Event(DeadOnTheGround);
        EventsQueue::instance().push(event);
        dealWithEvent();
        m_timer.restart();
    }
}

void PlayGame::draw() {
    m_window->clear();
    m_floor->draw(m_window);
    m_ceiling->draw(m_window);
    m_board.draw(m_window);
    for (auto  &nonCollisionObj : m_nonCollisionObj){
        nonCollisionObj->draw(m_window);
    }
    for (auto &singleObj : m_singleObj) {
        singleObj->draw(m_window);
    }
    for (auto &pairedObj : m_pairedObj) {
        if (pairedObj != m_pairedObj[m_pairedObj.size() - 1] || m_pairedObj.size() % 2 == 0) {
            pairedObj->draw(m_window);
        }
    }
    for (auto &missile : m_missiles) {
        missile->draw(m_window);
    }
    for (auto &fallingCoin : m_fallingCoins) {
        fallingCoin->draw(m_window);
    }
    m_window->draw(m_settingButton);
    m_scoreBoard.draw(m_window);
    if (m_flame->getInUse()) {
        m_flame->draw(m_window);
    }
    m_player->draw(m_window);
    m_window->display();
}

void PlayGame::dealWithCollision() {
    //Check if the player collision with coins
    float elapsed = m_collisionTimer.getElapsedTime().asSeconds();

    //Check if the player collision with coins
    for (auto &singleObj: m_singleObj) {
        m_player->handleCollision(*singleObj);
        singleObj->updateCollisionTime(elapsed);
    }
    std::erase_if(m_singleObj, [](const auto &item) {return item->getDelete();});
    m_collisionTimer.restart();

    //Check if the player collision with box2Coins
    for (auto &fallingCoin: m_fallingCoins) {
        m_player->handleCollision(*fallingCoin);
        fallingCoin->updateCollisionTime(elapsed);
    }
    std::erase_if(m_fallingCoins, [](const auto &item) {return item->getDelete();});

    //Check if the player collision with obstacles
    for (auto &pair: m_pairedObj) {
        m_player->handleCollision(*pair);
    }

    //Check if the player collision with missile
    for (auto &missile: m_missiles) {
        std::cout << "missile position: ( " << missile->getObject().getPosition().x << " , " << missile->getObject().getPosition().y << " )\n";
        m_player->handleCollision(*missile);
    }
    std::erase_if(m_missiles, [](const auto& item) { return item->getDelete(); });
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
                m_scoreBoard.addPoints(event.getPoints());
                sf::Vector2f position = event.getPiggyPosition();
                int random;
                srand(time(nullptr));
                for(int index = 0; index <= 80; index++) {
                    position.x += index / 4;
                    random = (rand() % 8) + 1;
                    m_fallingCoins.push_back(std::make_unique<Coin>(ResourcesManager::instance().getCoin(), position, m_world, random, B2DynamicCoin));
                }
                m_lastCoin = m_fallingCoins[m_fallingCoins.size() - 1]->getObject().getPosition();
                break;
            }
            case startSuperPower: {
                m_scoreBoard.addPoints(event.getPoints());
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
                break;
            }
            case DeadOnTheGround: {
                PlayerStateManager::instance().setState(GameOver, m_world);
                break;
            }
        }
    }
}
