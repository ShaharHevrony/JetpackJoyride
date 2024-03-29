#include "Event.h"
#include "PlayerStateManager.h"

Event::Event() {}

Event::Event(EventsTypes type, int points, const sf::Vector2f& position)
    : m_eventType(type), m_points(points), m_piggyPosition(position) {}

Event::~Event() {}

int Event::getPoints() const {
    return m_points;
}

void Event::setSuper() const {
    // Set the player's state to SuperPowerTank if not already in that state,
    // otherwise set it to SuperPowerRunner.
    if (!PlayerStateManager::instance().getIfSuperTank()) {
        PlayerStateManager::instance().setState(SuperPowerTank);
        PlayerStateManager::instance().setToSuperTank(true);
    }
    else {
        PlayerStateManager::instance().setState(SuperPowerRunner);
        PlayerStateManager::instance().setToSuperTank(false);
    }
}

std::vector<std::unique_ptr<Object>> Event::createFallingCoins() {
    std::vector<std::unique_ptr<Object>> fallingCoins;
    sf::Vector2f position = m_piggyPosition;
    b2World* world = PlayerStateManager::instance().getWorld();
    int random;
    srand(time(nullptr));
    for (int index = 0; index <= EIGHTY; index++) {
        position.x += index / FOUR;
        random = (rand() % BUTTON_NUM) + FIRST;
        // Create a falling coin object and add it to the vector.
        fallingCoins.push_back(std::make_unique<Coin>(ResourcesManager::instance().getCoin(), position, world, random, B2DynamicCoin));
    }
    return fallingCoins;
}

EventsTypes Event::getEventType() const {
    return m_eventType;
}
