#pragma once
#include "Values.h"
#include "Player.h"

class PlayerStateManager {
public:
    static PlayerStateManager& instance();
    void setState(int state);
    int getState() const;
    void setPlayer(std::shared_ptr<Box2Object> player);
    void setSpacePressed(bool pressed);
    bool getSpacePressed() const;
    void moveByState();
    void handleCollisionByState(float collidedType);

private:
    PlayerStateManager();
    ~PlayerStateManager();

    int m_state;
    bool m_wasSuper;
    std::shared_ptr<Box2Object> m_player;
    sf::Clock m_playerCollisionTime;   //Timer for tracking the time
    bool m_spacePressed = false;
};
