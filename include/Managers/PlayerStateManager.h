#pragma once
#include "Values.h"
#include "Player.h"

class PlayerStateManager {
public:
    static PlayerStateManager& instance();
    void setState(int state);
    int getState() const;
    bool wasSuperTank() const;
    void changeToSuperTank(bool change);
    void setPlayer(std::shared_ptr<Box2Object> player);
    void setSpacePressed(bool pressed);
    bool getSpacePressed() const;
    void moveByState();
    //void setGravity(b2World* m_world);
    void handleCollisionByState(float collidedType);

private:
    PlayerStateManager();
    ~PlayerStateManager();

    int m_state;
    bool m_wasSuper = false;
    bool m_spacePressed = false;
    bool m_wasSuperTank = false;
    std::shared_ptr<Box2Object> m_player;
    sf::Clock m_playerCollisionTime;   //Timer for tracking the time
};
