#include "Shop.h"

Shop::Shop(sf::RenderWindow& window): m_window(&window) {}

Shop::~Shop() {}

void Shop::create() {
    //create shop
    m_shopBoard.setTexture(*ResourcesManager::instance().getGameMenu());
    m_shopBoard.setScale(WINDOW_WIDTH / m_shopBoard.getTexture()->getSize().x, WINDOW_HEIGHT / m_shopBoard.getTexture()->getSize().y);

    m_backButton.setPosition(WINDOW_WIDTH / TEN, WINDOW_HEIGHT / BUTTON_NUM);
    m_backButton.setTexture(*ResourcesManager::instance().getQuitKey());
    m_backButton.setOrigin(m_backButton.getTexture()->getSize().x / DIV_TWO, m_backButton.getTexture()->getSize().y / DIV_TWO);
    GameManager::instance().setOwned(ZERO);

    //Define the size and position of the big rectangle
    sf::Vector2f rectSize(PLAYER_POS_X * SECOND + HUNDRED, PLAYER_POS_Y * SECOND + HUNDRED);
    sf::Vector2f rectPosition((WINDOW_WIDTH - rectSize.x) / DIV_TWO, (WINDOW_HEIGHT - rectSize.y) / DIV_TWO);

    //Draw the big rectangle
    sf::RectangleShape tempRec(rectSize);
    tempRec.setPosition(rectPosition);
    tempRec.setFillColor(sf::Color::White);
    m_characterRect = tempRec;
    setAvatar();
    m_window->draw(m_characterRect);
    m_rightArrow.setTexture(*ResourcesManager::instance().getArrow());
    m_rightArrow.setColor(sf::Color::White);
    m_leftArrow.setTexture(*ResourcesManager::instance().getArrow());
    m_rightArrow.setColor(sf::Color::White);
    m_buyButton.setPosition(SHOP_POS_X, rectPosition.y + rectSize.y + TWENTY);

    float arrowYPosition = rectPosition.y + (rectSize.y / SECOND);
    sf::Vector2f leftArrowPosition(rectPosition.x - HUNDRED * OBJECT_SCALE, arrowYPosition);
    sf::Vector2f rightArrowPosition(rectPosition.x + rectSize.x + HUNDRED * OBJECT_SCALE, arrowYPosition);

    // Set the positions and textures of the arrows
    m_rightArrow.setOrigin(m_rightArrow.getTexture()->getSize().x / DIV_TWO, m_rightArrow.getTexture()->getSize().y / DIV_TWO);
    m_leftArrow.setOrigin(m_leftArrow.getTexture()->getSize().x / DIV_TWO, m_leftArrow.getTexture()->getSize().y / DIV_TWO);
    m_rightArrow.setRotation(ONE_EIGHTY);
    m_leftArrow.setPosition(leftArrowPosition);
    m_leftArrow.setScale(PLAYER_SCALE / DIV_TWO, PLAYER_SCALE / DIV_TWO);
    m_rightArrow.setPosition(rightArrowPosition);
    m_rightArrow.setScale(PLAYER_SCALE / DIV_TWO, PLAYER_SCALE / DIV_TWO);

    for (int i = 0; i < playersAvatar.size(); i++) {
        sf::Text tempPrice("price: " + std::to_string(prices[i]), ResourcesManager::instance().getFont(), SETTING_SIZE);
        tempPrice.setPosition(SHOP_POS_X, SHOP_POS_Y / DIV_TWO);
        m_pricesText.push_back(tempPrice);
        sf::Text tempName(squareNames[i], ResourcesManager::instance().getFont(), SETTING_SIZE);
        tempName.setPosition(rectPosition.x + (rectSize.x / DIV_TWO) - (tempName.getLocalBounds().width / DIV_TWO),
                             rectPosition.y + rectSize.y + TWENTY);
        m_names.push_back(tempName);
    }
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
                case sf::Event::MouseButtonReleased: { //if the user clicks on the window
                    if (m_backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        return;
                    }
                    else if (m_leftArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        m_characterRect.setOutlineThickness(0);
                        m_avatarIndex--;
                        setAvatar();
                        break;
                    }
                    else if (m_rightArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        m_characterRect.setOutlineThickness(0);
                        m_avatarIndex++;
                        setAvatar();
                        break;
                    }
                    else if (m_buyButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        if (prices[m_avatarIndex] <= GameManager::instance().getCollectedSum() && !(GameManager::instance().getOwned(m_avatarIndex))) {
                            GameManager::instance().setOwned(m_avatarIndex);
                            GameManager::instance().setCollectedSumBuy(prices[m_avatarIndex]);
                            GameManager::instance().setCharacter(m_avatarIndex);
                            setAvatar();
                        }
                        else if (GameManager::instance().getOwned(m_avatarIndex)) {
                            GameManager::instance().setCharacter(m_avatarIndex);
                            setAvatar();
                            //set the equipped
                        }
                        break;
                    }
                }
                case sf::Event::MouseMoved: {
                    if (m_leftArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                        m_leftArrow.setScale(PLAYER_SCALE / ONE_POINT_FIVE, PLAYER_SCALE / ONE_POINT_FIVE);              //Increase left arrow size by 20%
                        m_rightArrow.setScale(PLAYER_SCALE / DIV_TWO, PLAYER_SCALE / DIV_TWO); //Reset right arrow size
                    }
                    else if (m_rightArrow.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                        m_rightArrow.setScale(PLAYER_SCALE / ONE_POINT_FIVE, PLAYER_SCALE / ONE_POINT_FIVE);             //Increase right arrow size by 20%
                        m_leftArrow.setScale(PLAYER_SCALE / DIV_TWO, PLAYER_SCALE / DIV_TWO); //Reset left arrow size

                    }
                    else {
                        m_leftArrow.setScale(PLAYER_SCALE / DIV_TWO, PLAYER_SCALE / DIV_TWO);  //Reset left arrow size
                        m_rightArrow.setScale(PLAYER_SCALE / DIV_TWO, PLAYER_SCALE / DIV_TWO); //Reset right arrow size
                    }
                    if (m_backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                        m_backButton.setScale(ONE_POINT_TWO, ONE_POINT_TWO);
                    } else {
                        m_backButton.setScale(FIRST, FIRST);
                    }
                    break;
                }
            }
        }
        draw();
    }
}

void Shop::setAvatar() {
    m_buyButton.setTexture(*ResourcesManager::instance().getBuy());
    int size = playersAvatar.size();
    if (m_avatarIndex > size - FIRST) {
        m_avatarIndex = ZERO;
    }
    else if (m_avatarIndex < ZERO) {
        m_avatarIndex = playersAvatar.size() - FIRST;
    }
    m_characterRect.setTexture(ResourcesManager::instance().getAvatar(m_avatarIndex));

    if (prices[m_avatarIndex] > GameManager::instance().getCollectedSum() && !(GameManager::instance().getOwned(m_avatarIndex))) {
        //Adjust the color of the texture to make it slightly grey
        sf::Color greyColor(ONE_TWENY_EIGHT, ONE_TWENY_EIGHT, ONE_TWENY_EIGHT, TWO_FIFTHY_FIVE);
        m_characterRect.setFillColor(greyColor);
        m_buyButton.setColor(greyColor);
    } else {
        //Reset the color to original
        m_characterRect.setFillColor(sf::Color::White);
        m_buyButton.setColor(sf::Color::White);
    }
    if (GameManager::instance().getOwned(m_avatarIndex)) {
        m_buyButton.setTexture(*ResourcesManager::instance().getEquip());
        //if not the equipped character so:
        if (GameManager::instance().getCharacter() != m_avatarIndex) {
            m_characterRect.setFillColor(sf::Color::White);
            m_buyButton.setColor(sf::Color::White);
        } else {
            sf::Color greyColor(ONE_TWENY_EIGHT, ONE_TWENY_EIGHT, ONE_TWENY_EIGHT, TWO_FIFTHY_FIVE);
            m_buyButton.setColor(greyColor);
        }
    }
}


void Shop::draw() {
    m_window->clear();
    m_window->draw(m_shopBoard);
    m_window->draw(m_characterRect);

    auto collectedSum = GameManager::instance().getCollectedSum();
    // Draw the money text
    sf::Text money("you have: " + std::to_string(collectedSum), ResourcesManager::instance().getFont(), SETTING_SIZE);
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