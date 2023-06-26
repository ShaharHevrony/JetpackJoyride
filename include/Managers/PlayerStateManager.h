#pragma once
#include "Values.h"
#include "Player.h"

class PlayerStateManager {
public:
    static PlayerStateManager& instance();
    void setState(int state, b2World* m_world);
    int getState() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getOrigin() const;
    sf::Vector2u getSize() const;
    bool getIfSuperTank() const;

    void setToSuperTank(bool change);
    void setPlayer(std::shared_ptr<Box2Object> player);
    void setSpacePressed(bool pressed);
    void animateByState();
    void moveByPress();
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
