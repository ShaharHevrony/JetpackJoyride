#include "PlayGame.h"

PlayGame::PlayGame(sf::RenderWindow& window) : m_window(&window) {
    //Initialize the Box2D world with specified gravity
    m_world = new b2World(b2Vec2(GRAVITATION_X, GRAVITATION_Y));

    //Create the floor and ceiling boundaries of the game
    m_floor = std::make_unique<Bound>(m_world, B2Floor);
    m_ceiling = std::make_unique<Bound>(m_world, B2Ceiling);

    //Create the player object and flame
    sf::Vector2f playerPosition(PLAYER_POS_X, PLAYER_POS_Y);
    m_player = std::make_shared<Player>(ResourcesManager::instance().getPlayerStates(GameManager::instance().getCharacter(), Regular), playerPosition, m_world, B2Player);
    m_flame = std::make_unique<Flame>(ResourcesManager::instance().getFlame(), playerPosition);
    PlayerStateManager::instance().setPlayer(m_player);
}

PlayGame::~PlayGame() {}

//Initialize game elements and settings
void PlayGame::create() {
    m_lastObjectX = LAST_POSITION;
    m_board.setBackgrounds();
    m_settingButton.setTexture(*ResourcesManager::instance().getGameSetting());
    m_settingButton.setPosition(GAME_SETTING_X, GAME_SETTING_Y);
    m_settingButton.setOrigin(m_settingButton.getTexture()->getSize().x / 2, m_settingButton.getTexture()->getSize().y / 2);
    m_settingButton.setScale(OBJECT_SCALE, OBJECT_SCALE);
    checkIfNeedToClear();
}

//The function represents the main game loop. It handles user input, updates game state, and renders the game.
void PlayGame::run() {
    //Create the game resources and initialize game settings
    create();
    GameSettings setting = GameSettings(*m_window);
    bool restartGame = false;

    //Main game loop
    while (m_window->isOpen() && !restartGame) {
        //Handle events
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
                //Handle the window being closed
                case sf::Event::Closed: {
                    m_window->close();
                    return;
                }
                //Handle key press events
                case sf::Event::KeyPressed: {
                    //Check if the Space key is pressed
                    if (event.key.code == sf::Keyboard::Space) {
                        //Set the spacePressed flag in the player state manager
                        PlayerStateManager::instance().setSpacePressed(true);
                        //Check the player state and set the flame in use if in regular state
                        if (PlayerStateManager::instance().getState() == Regular) {
                            m_flame->setInUse(true);
                        }
                    }
                    break;
                }
                //Handle key release events
                case sf::Event::KeyReleased: {
                    //Check if the Space key is released
                    if (event.key.code == sf::Keyboard::Space) {
                        //Set the spacePressed flag in the player state manager
                        PlayerStateManager::instance().setSpacePressed(false);
                        //Set the flame not in use
                        m_flame->setInUse(false);
                    }
                    break;
                }
                //Handle mouse button release events
                case sf::Event::MouseButtonReleased: {
                    //Check if the mouse button is released on the setting button
                    if (m_settingButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        //Check the potential best score, set the collected sum, and restart the game
                        GameManager::instance().checkPotentialBest(m_scoreBoard.getScore());
                        GameManager::instance().setCollectedSum(m_scoreBoard.getScore());
                        restartGame = setting.run(PlayerStateManager::instance().getState());
                        //Reset the clock and update the score
                        m_board.setClock();
                        m_scoreBoard.setScore();
                    }
                }
            }
        }
        if (restartGame) { //Check if the game is restarted
            GameManager::instance().setCollectedSum(m_scoreBoard.getScore());
        }
        animateObj(); //Perform object animation

        //Update game state if the player is not dead or game over
        if (PlayerStateManager::instance().getState() != DeadPlayer && PlayerStateManager::instance().getState() != GameOver) {
            //Check if objects need to be cleared, move objects, handle collisions, and deal with events
            checkIfNeedToClear();
            moveObj();
            dealWithCollision();
            dealWithEvent();
        }
        else {
            deathMoveObj(); //Move objects after player death
            if (PlayerStateManager::instance().getState() == GameOver) { //Check if the game is over
                // Check the elapsed time since game over and restart the game if necessary
                sf::Time elapsed = m_settingTimer.getElapsedTime();
                if (elapsed.asSeconds() >= 2.0) {
                    GameManager::instance().checkPotentialBest(m_scoreBoard.getScore());
                    GameManager::instance().setCollectedSum(m_scoreBoard.getScore());
                    m_scoreBoard.setScore();
                    restartGame = setting.run(PlayerStateManager::instance().getState());
                }
            }
        }
        deleteObj();
        draw();
    }
}
void PlayGame::createObjectMap() {
    m_board.randMap(); //Randomly generate the map
    sf::Vector2f position = sf::Vector2f(GAME_SETTING_X, GAME_SETTING_Y); //Set the initial position for the objects

    for (int row = 0; row < m_board.getMap().size(); row++) { //Iterate over each row in the map
        for (int col = 0; col < NUM_OF_OBJECTS; col++) {      //Iterate over each column in the map
            //Get the type of the object at the current position in the map
            char type = m_board.getMap()[row][col];
            //Calculate the position of the object based on the row and column indices
            position = sf::Vector2f(WINDOW_WIDTH + SETTING_SIZE * row, BOUND_POS_Y + SETTING_SIZE * col);
            //Create game objects based on the type
            switch (type) {
                case COIN: {
                    //Create a Coin object and add it to the single objects container
                    m_singleObj.push_back(std::make_unique<Coin>(ResourcesManager::instance().getCoin(), position, m_world, 1.f, B2StaticCoin));
                    break;
                }
                case LASER: {
                    //Create a Laser object and add it to the paired objects container
                    m_pairedObj.push_back(std::make_unique<Laser>(ResourcesManager::instance().getLaser(), position));
                    //Check if the number of paired objects is even
                    if (m_pairedObj.size() % 2 == 0) {
                        //Get the position of the previous laser object
                        sf::Vector2f otherPosition = m_pairedObj[m_pairedObj.size() - 2]->getObject().getPosition();
                        //Calculate the angle between the current and previous laser objects
                        m_pairedObj[m_pairedObj.size() - 1]->calculateAngle(otherPosition);
                        //Calculate the distance between the current and previous laser objects
                        float distance = m_pairedObj[m_pairedObj.size() - 2]->calculateDistance(position);
                        //Calculate the angle between the current and previous laser objects
                        float angle = m_pairedObj[m_pairedObj.size() - 2]->calculateAngle(position);
                        //Create a Beam object and add it to the single objects container
                        m_singleObj.push_back(std::make_unique<Beam>(ResourcesManager::instance().getLasersBeam(), position, angle,distance));
                        //Set the scale of the Beam object
                        m_singleObj[m_singleObj.size() - 1]->getObject().setScale(OBJECT_SCALE, distance/ResourcesManager::instance().getLasersBeam()->getSize().y);
                    }
                    break;
                }
                case MISSILE: {
                    //Create a Missile object and add it to the missiles container
                    m_missiles.push_back(std::make_unique<Missile>(ResourcesManager::instance().getMissile(0), position, m_missiles.size()));
                    break;
                }
                case PIGGY: {
                    //Create a Piggy object and add it to the single objects container
                    m_singleObj.push_back(std::make_unique<Piggy>(ResourcesManager::instance().getPiggy(), position));
                    break;
                }
                case SUPERPOWER: {
                    //Create a SuperPower object and add it to the single objects container
                    m_singleObj.push_back(
                            std::make_unique<SuperPower>(ResourcesManager::instance().getSuperPower(Box), position));
                    break;
                }
                default:
                    break;
            }
        }
    }
}
/**
 * Checks if objects need to be cleared and deletes objects that are out of range.
 * If objects need to be cleared, it clears the single objects, paired objects, and missiles containers,
 * generates a new random map on the board, and creates new objects on the map.
 */
void PlayGame::checkIfNeedToClear() {
    //Check if the last object's x position is less than or equal to the last position
    if (m_lastObjectX <= LAST_POSITION) {
        //Clear the containers of single objects, paired objects, and missiles
        m_singleObj.clear();
        m_pairedObj.clear();
        m_missiles.clear();
        m_board.randMap(); //Generate a new random map on the board
        createObjectMap(); //Create new objects on the map
    }
    //Delete objects that are out of range:

    //Iterate over each single object
    for (auto& singleObj : m_singleObj) {
        // Check if the x position of the object is less than or equal to the last position
        if (singleObj->getObject().getPosition().x <= LAST_POSITION) {
            singleObj->setDelete(); //Set the object for deletion
        }
    }

    //Iterate over each missile
    for (auto& missile : m_missiles) {
        // Check if the x position of the missile is less than or equal to the last position
        if (missile->getObject().getPosition().x <= LAST_POSITION) {
            missile->setDelete(); //Set the object for deletion
        }
    }

    //Iterate over each falling coin
    for (auto& fallingCoins : m_fallingCoins) {
        //Check if the x position of the falling coin is less than or equal to the last position
        if (fallingCoins->getObject().getPosition().x <= LAST_POSITION) {
            fallingCoins->setDelete(); //Set the object for deletion
        }
    }
}

/**
 * Animates the objects in the game.
 * It calls the animate() function for the flame, board, paired objects, single objects, falling coins, and missiles.
 * The flame and board are always animated. Paired objects are animated except for the last object if the number of
 * paired objects is even.
 */
void PlayGame::animateObj() {
    m_flame->animate(); //Animate the flame
    m_board.animate();  //Animate the board

    //Animate the paired objects (except for the last object if the number of paired objects is even)
    for (auto& pairedObj : m_pairedObj) {
        if (pairedObj != m_pairedObj[m_pairedObj.size() - 1] || m_pairedObj.size() % 2 == 0) {
            pairedObj->animate();
        }
    }
    for (auto& singleObj : m_singleObj) {      //Animate the single objects
        singleObj->animate();
    }
    for (auto& fallingCoin : m_fallingCoins) { //Animate the falling coins
        fallingCoin->animate();
    }
    for (auto& missile : m_missiles) {         //Animate the missiles
        missile->animate();
    }
}

/**
 * Moves the objects in the game.
 * It updates the lastObjectX variable with the maximum x position of the objects.
 * It moves the board backgrounds, player, flame, paired objects, single objects, missiles, and falling coins.
 */
void PlayGame::moveObj() {
    m_lastObjectX = LAST_POSITION; //Set the lastObjectX to the LAST_POSITION initially
    m_world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS); //Move the physics world

    m_board.moveBackgrounds(); //Move the board backgrounds
    float movement = m_board.getMovement(); //Get the movement from the board

    //Move the player and the flame
    m_player->move(movement);
    m_flame->move(movement);

    //Move the paired objects (except for the last object if the number of paired objects is even)
    for (auto& pairedObj : m_pairedObj) {
        if (pairedObj != m_pairedObj[m_pairedObj.size() - 1] || m_pairedObj.size() % 2 == 0) {
            pairedObj->move(movement);
            //Update the lastObjectX if the x position of the object is greater than the current lastObjectX
            if (pairedObj->getObject().getPosition().x >= m_lastObjectX) {
                m_lastObjectX = pairedObj->getObject().getPosition().x;
            }
        }
    }
    //Move the single objects
    for (auto& singleObj : m_singleObj) {
        singleObj->move(movement);
        //Update the lastObjectX if the x position of the object is greater than the current lastObjectX
        if (singleObj->getObject().getPosition().x >= m_lastObjectX) {
            m_lastObjectX = singleObj->getObject().getPosition().x;
        }
    }
    //Move the missiles
    for (auto& missile : m_missiles) {
        //Update the collision time of the missile with the board's time
        missile->updateCollisionTime(m_board.getTime());
        missile->move(movement);
        //Update the lastObjectX if the x position of the missile is greater than the current lastObjectX
        if (missile->getObject().getPosition().x >= m_lastObjectX) {
            m_lastObjectX = missile->getObject().getPosition().x;
        }
    }
    //Move the falling coins
    for (auto& fallingCoin : m_fallingCoins) {
        fallingCoin->move(movement);
    }
}


void PlayGame::dealWithCollision() {
    //check if the player collision with coins
    for (auto &singleObj: m_singleObj) {
        m_player->handleCollision(*singleObj);
    }
    //check if the player collision with box2Coins
    for (auto &fallingCoin: m_fallingCoins) {
        m_player->handleCollision(*fallingCoin);
    }
   //check if the player collision with obstacles
    for (auto &pair: m_pairedObj) {
        m_player->handleCollision(*pair);
    }
    //check if the player collision with missile
    for (auto &missile: m_missiles) {
        m_player->handleCollision(*missile);
    }
}

/**
 * Deals with events in the game.
 * Processes events from the event queue and performs appropriate actions based on the event type.
 * Events can include collecting money, collecting a piggy, starting a superpower, returning to regular state,
 * death in the air, and death on the ground.
 */
void PlayGame::dealWithEvent() {
    while (!EventsQueue::instance().empty()) {
        //Pop the next event from the event queue
        auto event = EventsQueue::instance().pop();

        //Process the event based on its event type
        switch (event.getEventType()) {
        case CollectedMoney: {
            //Add points to the score board based on the event's points value
            m_scoreBoard.addPoints(event.getPoints());
            break;
        }
        case CollectedPiggy: {
            //Add points to the score board based on the event's points value
            m_scoreBoard.addPoints(event.getPoints());

            //Create falling coins based on the event and assign them to the falling coins collection
            m_fallingCoins = event.createFallingCoins();
            break;
        }
        case startSuperPower: {
            //Add points to the score board based on the event's points value
            m_scoreBoard.addPoints(event.getPoints());

            //Set the player's state to super
            event.setSuper();
            break;
        }
        case ReturnRegular: {
            //Set the player's state to regular
            PlayerStateManager::instance().setState(Regular);
            break;
        }
        case DeathInTheAir: {
            //Set the player's state to dead player
            PlayerStateManager::instance().setState(DeadPlayer);
            break;
        }
        case DeadOnTheGround: {
            //Set the player's state to game over
            PlayerStateManager::instance().setState(GameOver);
            break;
        }
        }
    }
}

/**
 * Performs movement and actions related to the player's death.
 * Updates the positions and states of various game objects after the player's death.
 * Checks if the player has landed on the ground after falling, and triggers appropriate events.
 */
void PlayGame::deathMoveObj() {
    m_flame->setInUse(false); //Disable the flame animation
    m_world->Step(1.5 * TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS); //Step the physics world forward by 1.5 times the time step
    m_player->move(m_board.getMovement()); //Move the player based on the background movement
    //Check if the player has landed on the ground after falling
    if (std::abs(m_player->getBody()->GetLinearVelocity().x) <= VELOCITY_DELTA
        && std::abs(m_player->getBody()->GetLinearVelocity().y) <= VELOCITY_DELTA
        && PlayerStateManager::instance().getState() != GameOver
        && m_player->getObject().getPosition().y > HEIGHT_CENTER) {
        Event event = Event(DeadOnTheGround); //Create a DeadOnTheGround event
        EventsQueue::instance().push(event);  //Push the event to the event queue
        dealWithEvent();                      //Process the event
        m_settingTimer.restart();             //Restart the setting timer
    }
    //Move falling coins if they are above the floor position
    for (auto& fallingCoin : m_fallingCoins) {
        if (fallingCoin->getObject().getPosition().y <= BOUND_POS_Y) {
            fallingCoin->move(m_board.getMovement());
        }
    }
    //Move missiles based on the background movement
    for (auto& missile : m_missiles) {
        missile->move(m_board.getMovement());
    }
}
/**
 * Deletes game objects that have been marked for deletion.
 * Updates collision times for remaining game objects.
 * Restarts the collision timer.
 */
void PlayGame::deleteObj() {
    //Erase single objects marked for deletion
    std::erase_if(m_singleObj, [](const auto& item) { return item->getDelete(); });
    //Erase falling coins marked for deletion
    std::erase_if(m_fallingCoins, [](const auto& item) { return item->getDelete(); });
    //Erase missiles marked for deletion
    std::erase_if(m_missiles, [](const auto& item) { return item->getDelete(); });
    //Update collision times for remaining single objects
    float elapsed = m_collisionTimer.getElapsedTime().asSeconds();
    for (auto& singleObj : m_singleObj) {
        singleObj->updateCollisionTime(elapsed);
    }
    //Update collision times for remaining falling coins
    for (auto& fallingCoin : m_fallingCoins) {
        fallingCoin->updateCollisionTime(elapsed);
    }
    //Update collision times for remaining missiles
    for (auto& missile : m_missiles) {
        missile->updateCollisionTime(elapsed);
    }
    m_collisionTimer.restart(); //Restart the collision timer
}
void PlayGame::draw() {
    m_window->clear();         //Clear the window
    m_floor->draw(m_window);   //Draw the floor
    m_ceiling->draw(m_window); //Draw the ceiling
    m_board.draw(m_window);    //Draw the game board

    //Draw single objects
    for (auto& singleObj : m_singleObj) {
        singleObj->draw(m_window);
    }
    //Draw paired objects (except the last one if the number of objects is even)
    for (auto& pairedObj : m_pairedObj) {
        if (pairedObj != m_pairedObj[m_pairedObj.size() - 1] || m_pairedObj.size() % 2 == 0) {
            pairedObj->draw(m_window);
        }
    }
    //Draw missiles
    for (auto& missile : m_missiles) {
        missile->draw(m_window);
    }
    //Draw falling coins
    for (auto& fallingCoin : m_fallingCoins) {
        fallingCoin->draw(m_window);
    }
    m_window->draw(m_settingButton); //Draw the setting button
    m_scoreBoard.draw(m_window);     //Draw the score board
    if (m_flame->inUse()) {          //Draw the flame (if in use)
        m_flame->draw(m_window);
    }
    m_player->draw(m_window);       //Draw the player
    m_window->display();            //Display the window
}