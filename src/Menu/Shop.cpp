#include "Shop.h"

Shop::Shop(sf::RenderWindow& window): m_window(&window) {}

Shop::~Shop() {}

void Shop::create() {
    //create shop
    

    m_shopBoard.setTexture(*ResourcesManager::instance().getGameMenu());
    m_shopBoard.setScale(WINDOW_WIDTH / m_shopBoard.getTexture()->getSize().x, WINDOW_HEIGHT / m_shopBoard.getTexture()->getSize().y);

    m_backButton.setPosition(WINDOW_WIDTH / 10, WINDOW_HEIGHT / 8);
    m_backButton.setTexture(*ResourcesManager::instance().getQuitKey());
    m_backButton.setOrigin(m_backButton.getTexture()->getSize().x / 2, m_backButton.getTexture()->getSize().y / 2);

   


    // Define the size and position of the big rectangle
    sf::Vector2f rectSize(PLAYER_POS_X * 2 + 100, PLAYER_POS_Y * 2 + 100);
    sf::Vector2f rectPosition((WINDOW_WIDTH - rectSize.x) / 2, (WINDOW_HEIGHT - rectSize.y) / 2);

    // Draw the big rectangle
    sf::RectangleShape tempRec(rectSize);
    tempRec.setPosition(rectPosition);
    tempRec.setFillColor(sf::Color::White);
    m_characterRect = tempRec;
    setAvatar();
    m_window->draw(m_characterRect);


    m_rightArrow.setTexture(*ResourcesManager::instance().getArrow());
    m_leftArrow.setTexture(*ResourcesManager::instance().getArrow());

    float arrowYPosition = rectPosition.y + (rectSize.y / 2);

    sf::Vector2f leftArrowPosition(rectPosition.x - 100*OBJECT_SCALE, arrowYPosition);
    sf::Vector2f rightArrowPosition(rectPosition.x + rectSize.x + 100*OBJECT_SCALE, arrowYPosition);

    // Set the positions and textures of the arrows
    m_rightArrow.setOrigin(m_rightArrow.getTexture()->getSize().x / 2, m_rightArrow.getTexture()->getSize().y / 2);
    m_leftArrow.setOrigin(m_leftArrow.getTexture()->getSize().x / 2, m_leftArrow.getTexture()->getSize().y / 2);
    m_rightArrow.setRotation(180);
    m_leftArrow.setPosition(leftArrowPosition);
    m_leftArrow.setScale(PLAYER_SCALE/1.5, PLAYER_SCALE/1.5);
    m_rightArrow.setPosition(rightArrowPosition);
    m_rightArrow.setScale(PLAYER_SCALE/1.5, PLAYER_SCALE/1.5);

    for (int i = 0; i < playersAvatar.size(); i++) {
        sf::Text tempPrice("price: " + std::to_string(prices[i]), ResourcesManager::instance().getFont(), SCALE_SIZE);
        tempPrice.setPosition(SHOP_POS_X, SHOP_POS_Y / 2);
        m_pricesText.push_back(tempPrice);
        sf::Text tempName(squareNames[i], ResourcesManager::instance().getFont(), SCALE_SIZE);
        tempName.setPosition(rectPosition.x + (rectSize.x / 2) - (tempName.getLocalBounds().width / 2), rectPosition.y + rectSize.y + 20);
        m_names.push_back(tempName);
    }
    m_buyButton.setPosition(SHOP_POS_X, rectPosition.y + rectSize.y + 20);
    m_buyButton.setTexture(*ResourcesManager::instance().getBuy());
    //m_buyButton.setOrigin(m_backButton.getTexture()->getSize().x / 2, m_backButton.getTexture()->getSize().y / 2);
}


void Shop::run() {
    create();
    while (m_window->isOpen()) {
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    m_window->close();
                    return;
                }
                //if the user clicks on the window
                case sf::Event::MouseButtonReleased: {
                    if(m_backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
                        return;
                    }
                    if (m_leftArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        m_characterRect.setOutlineThickness(0);
                        m_avatarIndex--;
                        setAvatar();
                        break;
                    }
                    if (m_rightArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        m_characterRect.setOutlineThickness(0);
                        m_avatarIndex++;
                        setAvatar();
                        break;
                    }
                    if (m_characterRect.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        m_characterRect.setOutlineColor(sf::Color::Red);
                        m_characterRect.setOutlineThickness(7);
                        break;
                    }
                    if (m_buyButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) { //here is the connectiton to the game!!!!
                        if (prices[m_avatarIndex] < GameManager::instance().getCollectedSum()) {
                            GameManager::instance().setCollectedSum(-prices[m_avatarIndex]);
                            GameManager::instance().setCharacter(m_avatarIndex);
                        }
                        break;
                    }
                }
                case sf::Event::MouseMoved: {
                    if (m_leftArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                        m_leftArrow.setScale(PLAYER_SCALE, PLAYER_SCALE); // Increase left arrow size by 20%
                        m_rightArrow.setScale(PLAYER_SCALE / 1.5, PLAYER_SCALE / 1.5); // Reset right arrow size
                    }
                    else if (m_rightArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                        m_rightArrow.setScale(PLAYER_SCALE, PLAYER_SCALE); // Increase right arrow size by 20%
                        m_leftArrow.setScale(PLAYER_SCALE / 1.5, PLAYER_SCALE / 1.5); // Reset left arrow size
                        
                    }
                    else {
                        m_leftArrow.setScale(PLAYER_SCALE / 1.5, PLAYER_SCALE / 1.5); // Reset left arrow size
                        m_rightArrow.setScale(PLAYER_SCALE / 1.5, PLAYER_SCALE / 1.5); // Reset right arrow size
                    }
                    if (m_backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                        m_backButton.setScale(1.2, 1.2);
                    }
                    else {
                        m_backButton.setScale(1, 1);
                    }
                    break;
                }
            }
        }
        draw();
    }
}

void Shop::setAvatar() {
    if (m_avatarIndex > 1) {
        m_avatarIndex = 0;
    }
    else if (m_avatarIndex < 0) {
        m_avatarIndex = playersAvatar.size() - 1;
    }
    m_characterRect.setTexture(ResourcesManager::instance().getAvatar(m_avatarIndex));
    if (prices[m_avatarIndex] > GameManager::instance().getCollectedSum()) {
        // Adjust the color of the texture to make it slightly grey
        sf::Color greyColor(128, 128, 128, 255);
        m_characterRect.setFillColor(greyColor);
        m_buyButton.setColor(greyColor);
    }
    else {
        // Reset the color to its original state
        m_characterRect.setFillColor(sf::Color::White);
        m_buyButton.setColor(sf::Color::White);
    }
}


void Shop::draw() {
    m_window->clear();
    m_window->draw(m_shopBoard);
    m_window->draw(m_characterRect);
    
    auto collectedSum = GameManager::instance().getCollectedSum();
    // Draw the money text
    sf::Text money("you have: " + std::to_string(collectedSum), ResourcesManager::instance().getFont(), SCALE_SIZE);
    money.setPosition(SHOP_POS_X, SHOP_POS_Y);

    m_window->draw(money);
    m_window->draw(m_pricesText[m_avatarIndex]);
    m_window->draw(m_names[m_avatarIndex]);
    m_window->draw(m_buyButton);
    m_window->draw(m_backButton);
    m_window->draw(m_rightArrow);
    m_window->draw(m_leftArrow);
    m_window->display();
}
