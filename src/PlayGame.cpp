#include <SFML/Graphics.hpp>
#include "PlayGame.h"

sf::Clock PlayGame::gameTime;

PlayGame::PlayGame(sf::RenderWindow& window) : m_window(&window) {}

PlayGame::~PlayGame() {}

void PlayGame::create() {
    m_isDead = false;
    m_control.RandomCount_t.clear();
    createBarry();
    createObjectMap();
    m_board.setFirstBackground();
    m_board.setBackgrounds(BACKGROUND);
}

void PlayGame::createBarry(){
    sf::Vector2f playerPosition(250, 650);
    m_player = Player(ResourcesManager::instance().getPlayer(), playerPosition);
}

void PlayGame::createObjectMap(){
    //int random = randMap();
    sf::Vector2f position;
    int random = 7;
    for(int row = 0; row < m_board.getMap(random).size(); row++) {
            for(int col = 0; col < NUM_OF_OBJECTS; col++) {
                  char type = m_board.getMap(random)[row][col];
            position = sf::Vector2f(WINDOW_WIDTH + 55 * row, 40 + 55 * col);
            switch (type) {
                case COIN: {
                    m_singleObjects.push_back(std::make_unique<Coin>(ResourcesManager::instance().getCoin(), position));
                    if(lastObject == nullptr || position.x > lastObject->getObject().getPosition().x){
                        lastObject = std::make_unique<Coin>(ResourcesManager::instance().getCoin(), position);
                    }
                    break;
                }
                case OBSTACLE:{
                    m_pairedObjects.push_back(std::make_unique<Obstacle>(ResourcesManager::instance().getObstacle(), position));
                    if(m_pairedObjects.size() % 2 == 0){
                        m_pairedObjects[m_pairedObjects.size()-2]->setPaired(position);
                        m_pairedObjects[m_pairedObjects.size()-1]->setPaired(m_pairedObjects[m_pairedObjects.size()-2]->getObject().getPosition());
                        if(lastObject == nullptr || position.x > lastObject->getObject().getPosition().x){
                            lastObject = std::make_unique<Coin>(ResourcesManager::instance().getCoin(), position);
                        }
                       sf::Vector2f firstPosition = m_pairedObjects[m_pairedObjects.size() - 2]->getObject().getPosition();
                        // Calculate the distance between the two positions
                        double distance = calculateDistance(firstPosition.x, firstPosition.y, position.x, position.y);

                        // Calculate the number of additional sprites needed to cover the distance
                        int additionalSprites = static_cast<int>(distance ) - 1;

                        // Duplicate the sprite and set paired positions for the additional sprites
                        for (int i = 0; i < additionalSprites; ++i) {
                            sf::Vector2f newPosition = interpolatePosition(firstPosition, position, static_cast<float>(i + 1) / (additionalSprites + 1));
                            m_pairedObjects.push_back(std::make_unique<Obstacle>(ResourcesManager::instance().getLiserLine(), newPosition));
                            m_pairedObjects[m_pairedObjects.size() - 1]->setPaired(newPosition);
                        }
                    }
                    break;
                }
                case SPACE:{
                    break;
                }
            }
        }
    }
}

void PlayGame::run() {
    create();
    while (m_window->isOpen()){
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    m_window->close();
                    return;
                }
            }
        }
        if(lastObject->getObject().getPosition().x <= 0.f || lastObject == nullptr){
            createObjectMap();
        }
        draw();
    }
}

void PlayGame::dealWithCollision(){
    //check if the player collision with coins
    for (auto& mySingleObj : m_singleObjects) {
        m_player.handleCollision(*mySingleObj);
    }
    std::erase_if(m_singleObjects, [](const auto& item) {return item->getDelete();});

    
    //check if the player collision with obstacles
    for (auto& mypairObj : m_pairedObjects) {
        m_player.handleCollision(*mypairObj);
        if (mypairObj->getCollided()) {
            m_isDead = true;
        }
    }

}

void PlayGame::dealWithEvent() {
    while(!EventsQueue::instance().empty()) {
        auto event = EventsQueue::instance().pop();
        switch (event.getEventType()) {
            case CollectedMoney:{
                //add sound of money here
                m_scoreBoard.addPoints(event.getPoints());
                break;
            }
            case Death:{
                break;
            }
        }
    }
}

void PlayGame::draw(){
    m_window->clear();
    float changeInterval = 3.0f;
    float elapsedTime    = 0.0f;
    // Calculate the elapsed time in seconds
    m_control.Time_t = m_control.LoopClock_t.getElapsedTime().asSeconds();
    //every 5 seconds update the speed
    elapsedTime += m_control.Time_t;
    if (elapsedTime >= changeInterval) {
        m_control.Start_t += 15.f;
        elapsedTime -= changeInterval;
    }

    if(m_board.getBackgrounds()[0].getPosition().x <= 0 && m_board.getBackgrounds()[0].getPosition().x >= -1){
        m_board.setBorderPosition(2);
    } else if(m_board.getBackgrounds()[1].getPosition().x <= 0 && m_board.getBackgrounds()[1].getPosition().x >= -1){
        m_board.setBorderPosition(0);
    } else if(m_board.getBackgrounds()[2].getPosition().x <= 0 && m_board.getBackgrounds()[2].getPosition().x >= -1){
        m_board.setBorderPosition(1);
    }

    m_control.LoopClock_t.restart();
    m_board.moveBackgrounds(m_control.Time_t * m_control.Speed_t);
    for (int i = 0; i < BACKGROUND; ++i) {
        m_window->draw(m_board.getBackgrounds()[i]);
    }
    m_window->draw(m_board.getFirstBackground());

    moveObjects();
    for(int index = 0; index < m_pairedObjects.size(); index++){
        if(index != m_pairedObjects.size()-1 || m_pairedObjects.size() % 2 == 0){
            m_window->draw(m_pairedObjects[index]->getObject());
        }
    }
    for (int row = 0; row < m_singleObjects.size(); row++) {
        m_window->draw(m_singleObjects[row]->getObject());
    }
    m_scoreBoard.draw(*m_window);
    m_window->draw(m_player.getObject());
    m_window->display();
}

void PlayGame::moveObjects() {
    float time = gameTime.restart().asSeconds();
    lastObject->move(m_control.Time_t * m_control.Speed_t);

    for (int index = 0; index < m_pairedObjects.size(); index++) {
        if (index != m_pairedObjects.size() - 1 || m_pairedObjects.size() % 2 == 0) {
            m_pairedObjects[index]->animate();
            m_pairedObjects[index]->move(m_control.Time_t * m_control.Speed_t);
        }
    }

    for (int index = 0; index < m_singleObjects.size(); index++) {
        m_singleObjects[index]->animate();
        m_singleObjects[index]->move(m_control.Time_t * m_control.Speed_t);
    }
    if (m_isDead) {
        sf::Sprite tempSpr;
        for (int index = 0; index < 2; index++) {
            sf::Texture* tempTex = ResourcesManager::instance().getBarryDeath(index);
            tempSpr.setTexture(*tempTex);
            m_player.setSprite(tempSpr);
            m_player.playAnimationOnce(tempTex);

        }
    }
    else {
        m_player.animate();
        m_player.move(time);
    }


    dealWithCollision();
    dealWithEvent();


}

int PlayGame::randMap() {
    srand(time(nullptr));
    int random = rand() % MAP.size();
    if(m_control.RandomCount_t.size() != MAP.size()){
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

sf::Vector2f PlayGame::interpolatePosition(const sf::Vector2f& position1, const sf::Vector2f& position2, float t) {
    float x = position1.x + t * (position2.x - position1.x);
    float y = position1.y + t * (position2.y - position1.y);
    return sf::Vector2f(x, y);
}