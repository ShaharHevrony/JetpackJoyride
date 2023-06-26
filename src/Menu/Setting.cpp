#include "Setting.h"

Setting::Setting(sf::RenderWindow &window):m_window(&window) {}

void Setting::run() {
    create();
    while (m_window->isOpen()) {
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    GameManager::instance().setSound(m_sound.positionToVolume());
                    GameManager::instance().setMusic(m_music.positionToVolume());
                    GameManager::instance().setTopScore(m_topScore);
                    GameManager::instance().sort();
                    m_window->close();
                    return;
                }
                case sf::Event::MouseButtonPressed:{
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        //Check if the circle is clicked
                        if (m_music.getCircle().getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                            m_music.setGrabbed(true);
                        } else if (m_sound.getCircle().getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
                            m_sound.setGrabbed(true);
                        }
                        else if (m_backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                            GameManager::instance().setSound(m_sound.positionToVolume());
                            GameManager::instance().setMusic(m_music.positionToVolume());
                            GameManager::instance().setTopScore(m_topScore);
                            GameManager::instance().sort();
                            return;
                        }
                    }
                    break;
                }
                case sf::Event::MouseButtonReleased:{
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        m_music.setGrabbed(false);
                        m_sound.setGrabbed(false);
                    }
                    break;
                }
                case sf::Event::MouseMoved: {
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

void Setting::draw() {
    m_window->clear();
    m_window->draw(m_settingBoard);

    for(int index = 0; index < TOP_FIVE; index++){
        m_window->draw(m_topBoard[index]);
        m_window->draw(m_topText[index]);
    }

    sf::Vertex musicLine[] = {
            sf::Vertex(m_music.getStart(), sf::Color(150, 150, 150)),
            sf::Vertex(m_music.getEnd(), sf::Color(150, 150, 150))
    };
    m_window->draw(musicLine, 2, sf::Lines);
    m_window->draw(m_music.getCircle());

    sf::Vertex soundLine[] = {
            sf::Vertex(m_sound.getStart(), sf::Color(150, 150, 150)),
            sf::Vertex(m_sound.getEnd(), sf::Color(150, 150, 150))
    };
    m_window->draw(soundLine, 2, sf::Lines);
    m_window->draw(m_sound.getCircle());

    m_window->draw(m_backButton);
    m_window->draw(m_backText);

    m_window->display();
}

void Setting::create() {
    setTopText();
    int sound = 1;
    int music = 2;
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
        m_topBoard[index].setSize(sf::Vector2f (m_music.getStart().x - m_music.getEnd().x, SCALE_SIZE * 1.5));
        m_topBoard[index].setPosition(sf::Vector2f(WIDTH_CENTER * 1.35, HEIGHT_CENTER + SCALE_SIZE * 1.5 * index)); //-position.y));
        m_topBoard[index].setOrigin(m_topBoard->getSize().x/2, m_topBoard->getSize().y/2);
        m_topBoard[index].setFillColor(sf::Color(97,106,132));
        m_topBoard[index].setOutlineThickness(2);
        m_topBoard[index].setOutlineColor(sf::Color::Black);

        m_topText[index].setPosition(m_topBoard[index].getPosition().x, m_topBoard[index].getPosition().y - SCALE_SIZE/5);
        m_topText[index].setOrigin(m_topText[index].getLocalBounds().width/2, m_topText[index].getLocalBounds().height/2);
        m_topText[index].setFillColor(sf::Color::White);
        m_topText[index].setOutlineColor(sf::Color::Black);
        m_topText[index].setOutlineThickness(3);
    }

    m_backButton.setPosition(WIDTH_CENTER + OBJECT_SCALE * 26, m_music.getStart().y + OBJECT_SCALE * 26);
    m_backButton.setOrigin(WIDTH_CENTER - 2 * OBJECT_SCALE, m_music.getStart().y);
    m_backButton.setTexture(*ResourcesManager::instance().getQuitKey());
}

Setting::~Setting() {}

void Setting::setTopText() {
    GameManager::instance().sort();
    for(int i = 0; i < TOP_FIVE; i++) {
        m_topText[i] = sf::Text(std::to_string(GameManager::instance().getTopScore(i)), ResourcesManager::instance().getFont(), SCALE_SIZE);
    }
}