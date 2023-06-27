#include "PlayerStateManager.h"

PlayerStateManager::PlayerStateManager() {
    //Initialize the player state manager
    m_state = Regular;
    m_wasSuper = false;
    m_playerCollisionTime.restart();
}

PlayerStateManager& PlayerStateManager::instance() {
    try { //Create and return the instance of PlayerStateManager using the singleton pattern
        static PlayerStateManager m_instance;
        return m_instance;
    }
    catch (std::exception& e) { //Handle any exceptions that occur during instance creation
        std::cout << e.what() << std::endl;
        throw;
    }
}

//Destructor
PlayerStateManager::~PlayerStateManager() {}

//Set the player object
void PlayerStateManager::setPlayer(std::shared_ptr<Box2Object> player) {
    m_player = player;
    setState(Regular);
}

//Set the state of the space-bar
void PlayerStateManager::setSpacePressed(bool pressed) {
    m_spacePressed = pressed;
}

void PlayerStateManager::setState(int state) {
    m_spacePressed = true;
    b2World* world = m_player->getBody()->GetWorld();
    b2Vec2 gravity = world->GetGravity();
    m_state = state;
    switch (m_state) {
        case Regular: {          //Set the player animation and gravity for the regular state
            m_player->setAnimate(ResourcesManager::instance().getPlayerStates(GameManager::instance().getCharacter(), Regular), DEFAULT_ANIMATION, DEFAULT_SPEED);
            gravity = b2Vec2(GRAVITATION_X, GRAVITATION_Y);
            break;
        }
        case SuperPowerTank: {   //Set the player animation and gravity for the tank superpower state
            m_player->setAnimate(ResourcesManager::instance().getSuperPower(WalkingTank), sf::Vector2u(2, 1), DEFAULT_SPEED);
            gravity = b2Vec2(GRAVITATION_X, GRAVITATION_Y);
            break;
        }
        case SuperPowerRunner: { //Set the player animation and gravity for the runner superpower state
            m_player->setAnimate(ResourcesManager::instance().getSuperPower(Runner), DEFAULT_ANIMATION, DEFAULT_SPEED);
            gravity = b2Vec2(-GRAVITATION_X, -GRAVITATION_Y);
            break;
        }
        case DeadPlayer: {       //Set the player animation and gravity for the dead player state
            m_player->setAnimate(ResourcesManager::instance().getPlayerStates(GameManager::instance().getCharacter(), DeadPlayer), DEFAULT_ANIMATION, DEFAULT_SPEED);
            gravity = b2Vec2(DEATH_GRAVITY_X, DEATH_GRAVITY_Y);
            break;
        }
        case GameOver: {         //Set the player animation and gravity for the game over state
            m_player->setAnimate(ResourcesManager::instance().getPlayerStates(GameManager::instance().getCharacter(), GameOver), sf::Vector2u(1, 1), DEFAULT_SPEED);
            gravity = b2Vec2(DEATH_GRAVITY_X, GRAVITATION_Y);
            break;
        }
        default:
            break;
    }
    world->SetGravity(gravity);
    m_player->getObject().setScale(PLAYER_SCALE, PLAYER_SCALE);
    m_player->getObject().setOrigin(m_player->getObject().getTextureRect().width/2, m_player->getObject().getTextureRect().height);
    moveByPress();
    m_spacePressed = false;
}

int PlayerStateManager::getState() const {
    return m_state;
}

sf::Vector2f PlayerStateManager::getPosition() const {
    return m_player->getObject().getPosition();
}

sf::Vector2f PlayerStateManager::getOrigin() const {
    return m_player->getObject().getOrigin();
}

sf::Vector2u PlayerStateManager::getSize() const {
    return m_player->getObject().getTexture()->getSize();
}

b2World *PlayerStateManager::getWorld() const {
    return m_player->getBody()->GetWorld();
}

bool PlayerStateManager::getIfSuperTank() const {
    return m_wasSuperTank;
}

void PlayerStateManager::setToSuperTank(bool change){
    m_wasSuperTank = change;
}

//Updates the player's movement based on key presses.
void PlayerStateManager::moveByPress() {
    float jumpVelocity;                                          //Set the initial jump velocity to the value of ANTI_GRAVITY
    if (m_spacePressed) {                                        //Adjust the jump velocity based on the player's state
        switch (m_state) {
            case Regular: {
                jumpVelocity = ANTI_GRAVITY * GRAVITATION_Y;     //Adjust the jump velocity as needed
                break;
            }
            case SuperPowerTank: {
                jumpVelocity = ANTI_GRAVITY / 2 * GRAVITATION_Y; //Adjust the jump velocity as needed
                break;
            }
            case SuperPowerRunner: {
                jumpVelocity = - ANTI_GRAVITY * GRAVITATION_Y;    //Adjust the jump velocity as needed
                break;
            }
            default:{

                break;
            }
        }
        if (m_state != DeadPlayer && m_state != GameOver) {
            //Set the linear velocity of the player's physics body
            m_player->getBody()->SetLinearVelocity(b2Vec2(m_player->getBody()->GetLinearVelocity().x, jumpVelocity));
            //Update the position and rotation of the graphical object based on the physics body
            b2Vec2 bodyPosition = m_player->getBody()->GetPosition();
            float bodyAngle = m_player->getBody()->GetAngle();
            m_player->getObject().setPosition(bodyPosition.x, bodyPosition.y);
            m_player->getObject().setRotation(bodyAngle * ANGLE_CALC);
        }
    }
}

//Animates the player's graphical object based on its state.
void PlayerStateManager::animateByState() {
    float length = m_player->getObject().getTexture()->getSize().x / 4; //Calculate the length of each animation frame

    switch (m_state) {  //Switch statement based on the player's state
        case Regular: { //Check if the space key is pressed
            if (m_spacePressed) {
                //Set the texture rectangle of the player's graphical object to display the third frame
                m_player->getObject().setTextureRect(sf::IntRect(length * 3, 0, length, m_player->getObject().getTexture()->getSize().y));
            } else if (m_player->getBody()->GetLinearVelocity().y > 0.0f) {  //Check if the player's body is moving upward
                //Set the texture rectangle of the player's graphical object to display the second frame
                m_player->getObject().setTextureRect(sf::IntRect(length * 2, 0, length, m_player->getObject().getTexture()->getSize().y));
            } else { //If none of the above conditions are met, call the animate() function of the player object
                m_player->animate();
            }
            break;
        }
        case SuperPowerTank: {    //Check if the space key is pressed
            if (m_spacePressed) { //Set the animation of the player's graphical object to the "FlyingTank" superpower animation
                m_player->setAnimate(ResourcesManager::instance().getSuperPower(FlyingTank), sf::Vector2u(1, 1), DEFAULT_SPEED);
            } else {
                //Check if the player's body is moving upward
                if (m_player->getBody()->GetLinearVelocity().y > 0.f) {
                    //Set the animation of the player's graphical object to the "WalkingTank" superpower animation and adjust the length
                    m_player->setAnimate(ResourcesManager::instance().getSuperPower(WalkingTank), sf::Vector2u(2, 1), DEFAULT_SPEED);
                    length *= 2;
                    //Set the texture rectangle of the player's graphical object to display the adjusted length
                    m_player->getObject().setTextureRect(sf::IntRect(length, 0, length, m_player->getObject().getTexture()->getSize().y));
                } else { //If none of the above conditions are met, call the animate() function of the player object
                    m_player->animate();
                }
            }
            break;
        }
        case SuperPowerRunner: {
            //Check if the space key is pressed
            if (m_spacePressed) {
                //Set the texture rectangle of the player's graphical object to display the second frame
                m_player->getObject().setTextureRect(sf::IntRect(length * 2, 0, length, m_player->getObject().getTexture()->getSize().y));
            } else if (m_player->getBody()->GetLinearVelocity().y > 0.0f) { //Check if the player's body is moving upward
                //Set the texture rectangle of the player's graphical object to display the first frame
                m_player->getObject().setTextureRect(sf::IntRect(length * 0, 0, length, m_player->getObject().getTexture()->getSize().y));
            } else { //If none of the above conditions are met, call the animate() function of the player object
                m_player->animate();
            }
            break;
        }
        case DeadPlayer: {
            m_player->animate();
            break;
        }
        case GameOver: {
            m_player->getBody()->SetLinearVelocity(b2Vec2{0,0});
            m_player->animate();
            break;
        }
        default:
            break;
    }
}

//Handles collisions based on the player's state and the type of object collided with.
void PlayerStateManager::handleCollisionByState(float collidedType) {
    //Get the elapsed time since the player's collision
    float elapse = m_playerCollisionTime.getElapsedTime().asSeconds();
    //Switch statement based on the player's state
    switch (m_state) {
        case Regular: {
            //Check if enough time has passed since the collision or if the player was not in a super state previously
            if (elapse >= collidedType || !m_wasSuper) {
                //Create a DeathInTheAir event and push it to the event queue
                Event event = Event(DeathInTheAir);
                EventsQueue::instance().push(event);
                m_wasSuper = true; //Set the wasSuper flag to true
            }
            break;
        }
        case SuperPowerTank: {
            //Create a ReturnRegular event and push it to the event queue
            Event event = Event(ReturnRegular);
            EventsQueue::instance().push(event);
            m_playerCollisionTime.restart(); //Restart the player collision timer
            m_wasSuper = true;               //Set the wasSuper flag to true
            break;
        }
        case SuperPowerRunner: {
            //Create a ReturnRegular event and push it to the event queue
            Event event = Event(ReturnRegular);
            EventsQueue::instance().push(event);
            m_playerCollisionTime.restart(); //Restart the player collision timer
            m_wasSuper = true;               //Set the wasSuper flag to true
            break;
        }
        default:
            break;
    }
}