
#include "Setting.h"

Setting::Setting(sf::RenderWindow& window) : m_window(&window) {
    m_renderTexture.create(window.getSize().x, window.getSize().y);
}

Setting::~Setting() {}

void Setting::create() {
    sortTopFive();
    m_settingBoard.setSize(sf::Vector2f(m_window->getSize().x/2 ,m_window->getSize().y/10*8));
    m_settingBoard.setPosition(m_window->getSize().x/2, m_window->getSize().y/2);
    m_settingBoard.setOrigin(m_settingBoard.getSize().x/2, m_settingBoard.getSize().y/2);
    m_settingBoard.setFillColor(sf::Color(245,208,208));

    float circleRadius = 20.f;
    float positionX = m_settingBoard.getPosition().x/6;
    float positionY = m_settingBoard.getPosition().y/6;

    m_music.Start_t = sf::Vector2f(m_settingBoard.getPosition().x - positionX, m_settingBoard.getPosition().y - 3 * positionY);
    m_music.End_t = sf::Vector2f(m_settingBoard.getPosition().x + positionX ,m_settingBoard.getPosition().y - 3 * positionY);

    m_music.Circle_t.setRadius(circleRadius);
    m_music.Circle_t.setFillColor(sf::Color(150,150,150));
    m_music.Circle_t.setOrigin(circleRadius, circleRadius);
    m_music.Circle_t.setPosition(m_music.Start_t.x, m_music.End_t.y);
    m_music.Type_t = sf::Text("MUSIC", ResourcesManager::instance().getFont(), 50);
    m_music.Type_t.setFillColor(sf::Color(150,150,150));
    m_music.Type_t.setPosition(m_settingBoard.getPosition().x - 60, m_settingBoard.getPosition().y - 4 * positionY);

    m_sound.Start_t = sf::Vector2f(m_settingBoard.getPosition().x - positionX, m_settingBoard.getPosition().y - positionY);
    m_sound.End_t = sf::Vector2f(m_settingBoard.getPosition().x + positionX ,m_settingBoard.getPosition().y - positionY);

    m_sound.Circle_t.setRadius(circleRadius);
    m_sound.Circle_t.setFillColor(sf::Color(150,150,150));
    m_sound.Circle_t.setOrigin(circleRadius, circleRadius);
    m_sound.Circle_t.setPosition(m_sound.Start_t.x, m_sound.End_t.y);
    m_sound.Type_t = sf::Text("SOUND", ResourcesManager::instance().getFont(), 50);
    m_sound.Type_t.setPosition(m_settingBoard.getPosition().x - 60, m_settingBoard.getPosition().y - 2 * positionY);
    m_sound.Type_t.setFillColor(sf::Color(150,150,150));

    for(int index = 0; index < TOP_FIVE; index++){
        m_topBoard[index].setSize(sf::Vector2f (m_music.Start_t.x - m_music.End_t.x, 70));
        m_topBoard[index].setPosition(sf::Vector2f(m_settingBoard.getPosition().x, m_settingBoard.getPosition().y + 70 * index));
        m_topBoard[index].setOrigin(m_topBoard->getSize().x/2, m_topBoard->getSize().y/2);
        m_topBoard[index].setFillColor(sf::Color(245,222,222));
        m_topBoard[index].setOutlineThickness(2);
        m_topBoard[index].setOutlineColor(sf::Color(150,150,150));

        m_topText[index].setPosition(m_topBoard[index].getPosition().x - 50, m_topBoard[index].getPosition().y - 30);
        m_topText[index].setFillColor(sf::Color(150,150,150));
    }
}

void Setting::run() {
    create();
    while (m_window->isOpen()){
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    m_window->close();
                    return;
                }
                case sf::Event::MouseButtonPressed:{
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        // Check if the circle is clicked
                        if (m_music.Circle_t.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                            m_music.CircleGrabbed_t = true;
                        } else if (m_sound.Circle_t.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
                            m_sound.CircleGrabbed_t = true;
                        }
                    }
                    break;
                }
                case sf::Event::MouseButtonReleased:{
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        m_music.CircleGrabbed_t = false;
                        m_sound.CircleGrabbed_t = false;
                    }
                    break;
                }
                case sf::Event::MouseMoved: {
                    if (m_music.CircleGrabbed_t || m_sound.CircleGrabbed_t) {
                        // Update circle position based on mouse movement
                        if (m_music.Circle_t.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                            float circle2X = static_cast<float>(event.mouseMove.x);
                            if (circle2X < m_music.Start_t.x) {
                                m_music.Circle_t.setPosition(m_music.Start_t.x, m_music.Start_t.y);
                            } else if (circle2X > m_music.End_t.x) {
                                m_music.Circle_t.setPosition(m_music.End_t.x, m_music.End_t.y);
                            } else {
                                m_music.Circle_t.setPosition(circle2X, m_music.Start_t.y);
                            }
                        }

                        if (m_sound.Circle_t.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                            float circle2X = static_cast<float>(event.mouseMove.x);
                            if (circle2X < m_sound.Start_t.x) {
                                m_sound.Circle_t.setPosition(m_sound.Start_t.x, m_sound.Start_t.y);
                            } else if (circle2X > m_sound.End_t.x) {
                                m_sound.Circle_t.setPosition(m_sound.End_t.x, m_sound.End_t.y);
                            } else {
                                m_sound.Circle_t.setPosition(circle2X, m_sound.Start_t.y);
                            }
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }
        draw();
    }
}

void Setting::draw() {
    m_renderTexture.clear(sf::Color(220, 220, 220, 1));
    m_renderTexture.display();
    sf::Sprite renderSprite(m_renderTexture.getTexture());
    m_window->draw(renderSprite);
    m_window->draw(m_settingBoard);

    sf::Vertex musicLine[] = {
        sf::Vertex(m_music.Start_t, sf::Color(150, 150, 150)),
        sf::Vertex(m_music.End_t, sf::Color(150, 150, 150))
    };
    m_window->draw(musicLine, 2, sf::Lines);
    m_window->draw(m_music.Type_t);
    m_window->draw(m_music.Circle_t);

    sf::Vertex soundLine[] = {
        sf::Vertex(m_sound.Start_t, sf::Color(150, 150, 150)),
        sf::Vertex(m_sound.End_t, sf::Color(150, 150, 150))
    };
    m_window->draw(soundLine, 2, sf::Lines);
    m_window->draw(m_sound.Type_t);
    m_window->draw(m_sound.Circle_t);

    for(int index = 0; index < TOP_FIVE; index++){
        m_window->draw(m_topBoard[index]);
    }
    for(int index = 0; index < TOP_FIVE; index++){
        m_window->draw(m_topText[index]);
    }
    m_window->display();
}

void Setting::readFile() {}

void Setting::writeFile() {}

void Setting::sortTopFive() {
    for (int i = 0; i < TOP_FIVE - 1; ++i) {
        for (int j = 0; j < TOP_FIVE - i - 1; ++j) {
            if (m_topScore[j] > m_topScore[j + 1]) {
                int temp = m_topScore[j];
                m_topScore[j] = m_topScore[j + 1];
                m_topScore[j + 1] = temp;
            }
        }
    }
    for(int i = 0; i < TOP_FIVE; i++){
        m_topText[i] = sf::Text(std::to_string(m_topScore[i]), ResourcesManager::instance().getFont(), 50);
    }
}

void Setting::checkNewRecord(int score) {
    sortTopFive();
    if (score > m_topScore[0]){
        m_topScore[0] = score;
        sortTopFive();
    }
}

void Setting::calculatePercentage() {
    sf::Vector2f lineVector = m_music.End_t - m_music.Start_t;
    float lineLength = std::sqrt(lineVector.x * lineVector.x + lineVector.y * lineVector.y);
    sf::Vector2f circleVector = m_music.Circle_t.getPosition() - m_music.Start_t;
    float circleDistance = std::sqrt(circleVector.x * circleVector.x + circleVector.y * circleVector.y);
    m_music.Percentage_t = (circleDistance / lineLength) * 100.f;

    lineVector = m_sound.End_t - m_sound.Start_t;
    lineLength = std::sqrt(lineVector.x * lineVector.x + lineVector.y * lineVector.y);
    circleVector = m_sound.Circle_t.getPosition() - m_sound.Start_t;
    circleDistance = std::sqrt(circleVector.x * circleVector.x + circleVector.y * circleVector.y);
    m_sound.Percentage_t = (circleDistance / lineLength) * 100.f;
}
