#include "Settings.h"

Settings::Settings(sf::RenderWindow& window) : m_window(&window) {}

void Settings::run() {
    create();
    while (m_window->isOpen()) {
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed: {
                // Save settings and close the window when the "Closed" event is triggered
                GameManager::instance().setSound(m_sound.positionToVolume());
                GameManager::instance().setMusic(m_music.positionToVolume());
                GameManager::instance().setTopScore(m_topScore);
                GameManager::instance().sort();
                m_window->close();
                return;
            }
            case sf::Event::MouseButtonPressed: {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if the music circle or sound circle is clicked
                    if (m_music.getCircle().getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        m_music.setGrabbed(true);
                    }
                    else if (m_sound.getCircle().getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        m_sound.setGrabbed(true);
                    }
                    else if (m_backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        // Save settings and return when the back button is clicked
                        GameManager::instance().setSound(m_sound.positionToVolume());
                        GameManager::instance().setMusic(m_music.positionToVolume());
                        GameManager::instance().setTopScore(m_topScore);
                        GameManager::instance().sort();
                        return;
                    }
                }
                break;
            }
            case sf::Event::MouseButtonReleased: {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Reset the grabbed state when the mouse button is released
                    m_music.setGrabbed(false);
                    m_sound.setGrabbed(false);
                }
                break;
            }
            case sf::Event::MouseMoved: {
                // Handle mouse movement for the music and sound circles
                sf::Vector2f mouseMoved = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                m_music.handleMouseMoved(mouseMoved);
                m_sound.handleMouseMoved(mouseMoved);
                break;
            }
            }
        }
        draw();
    }
}

void Settings::draw() {
    m_window->clear();
    m_window->draw(m_settingBoard);

    for (int index = 0; index < TOP_FIVE; index++) {
        m_window->draw(m_topBoard[index]);
        m_window->draw(m_topText[index]);
    }

    sf::Vertex musicLine[] = {
            sf::Vertex(m_music.getStart(), sf::Color(ONE_FIFTHY, ONE_FIFTHY, ONE_FIFTHY)),
            sf::Vertex(m_music.getEnd(), sf::Color(ONE_FIFTHY, ONE_FIFTHY, ONE_FIFTHY))
    };
    m_window->draw(musicLine, SECOND, sf::Lines);
    m_window->draw(m_music.getCircle());

    sf::Vertex soundLine[] = {
            sf::Vertex(m_sound.getStart(), sf::Color(ONE_FIFTHY, ONE_FIFTHY, ONE_FIFTHY)),
            sf::Vertex(m_sound.getEnd(), sf::Color(ONE_FIFTHY, ONE_FIFTHY, ONE_FIFTHY))
    };
    m_window->draw(soundLine, SECOND, sf::Lines);
    m_window->draw(m_sound.getCircle());

    m_window->draw(m_backButton);
    m_window->draw(m_backText);

    m_window->display();
}

void Settings::create() {
    setTopText();
    int sound = FIRST;
    int music = SECOND;
    m_settingBoard.setTexture(*ResourcesManager::instance().getSettingBackGround());
    m_settingBoard.setScale(WINDOW_WIDTH / m_settingBoard.getTexture()->getSize().x, WINDOW_HEIGHT / m_settingBoard.getTexture()->getSize().y);
    m_sound.create(sound);
    m_sound.setVolume(GameManager::instance().getSound());
    m_music.create(music);
    m_music.setVolume(GameManager::instance().getMusic());

    for(int index = 0; index < TOP_FIVE; index++) {
        m_topScore[index] = GameManager::instance().getTopScore(index);
    }

    for(int index = 0; index < TOP_FIVE; index++) {
        m_topBoard[index].setSize(sf::Vector2f (m_music.getStart().x - m_music.getEnd().x, SETTING_SIZE * ONE_POINT_FIVE));
        m_topBoard[index].setPosition(sf::Vector2f(WIDTH_CENTER * ONE_POINT_THIRTY_FIVE, HEIGHT_CENTER + SETTING_SIZE * ONE_POINT_FIVE * index)); //-position.y));
        m_topBoard[index].setOrigin(m_topBoard->getSize().x/DIV_TWO, m_topBoard->getSize().y/DIV_TWO);
        m_topBoard[index].setFillColor(sf::Color(97,106,132));
        m_topBoard[index].setOutlineThickness(SECOND);
        m_topBoard[index].setOutlineColor(sf::Color::Black);

        m_topText[index].setPosition(m_topBoard[index].getPosition().x, m_topBoard[index].getPosition().y - SETTING_SIZE / FIVE_F);
        m_topText[index].setOrigin(m_topText[index].getLocalBounds().width/DIV_TWO, m_topText[index].getLocalBounds().height/DIV_TWO);
        m_topText[index].setFillColor(sf::Color::White);
        m_topText[index].setOutlineColor(sf::Color::Black);
        m_topText[index].setOutlineThickness(3);
    }

    m_backButton.setPosition(WIDTH_CENTER + OBJECT_SCALE * TWENTY_SIX, m_music.getStart().y + OBJECT_SCALE * TWENTY_SIX);
    m_backButton.setOrigin(WIDTH_CENTER - SECOND * OBJECT_SCALE, m_music.getStart().y);
    m_backButton.setTexture(*ResourcesManager::instance().getQuitKey());
}

Settings::~Settings() {}

void Settings::setTopText() {
    GameManager::instance().sort();
    for(int i = 0; i < TOP_FIVE; i++) {
        m_topText[i] = sf::Text(std::to_string(GameManager::instance().getTopScore(i)), ResourcesManager::instance().getFont(), SETTING_SIZE);
    }
}