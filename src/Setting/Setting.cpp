
#include "Setting/Setting.h"

Setting::Setting(sf::RenderWindow &window):m_window(&window) {
    m_renderTexture.create(window.getSize().x, window.getSize().y);
}

void Setting::run() {
    create();
    while (m_window->isOpen()) {
        if (auto event = sf::Event{}; m_window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    writeFile();
                    m_window->close();
                    return;
                }
                case sf::Event::MouseButtonPressed:{
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        // Check if the circle is clicked
                        if (m_music.getCircle().getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                            m_music.setGrabbed(true);
                        } else if (m_sound.getCircle().getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
                            m_sound.setGrabbed(true);
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
    m_renderTexture.clear(sf::Color(220, 220, 220, 1));
    m_renderTexture.display();
    sf::Sprite renderSprite(m_renderTexture.getTexture());
    m_window->draw(renderSprite);
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
    m_music.setType("MUSIC: ");
    m_window->draw(m_music.getType());
    m_window->draw(m_music.getCircle());

    sf::Vertex soundLine[] = {
        sf::Vertex(m_sound.getStart(), sf::Color(150, 150, 150)),
        sf::Vertex(m_sound.getEnd(), sf::Color(150, 150, 150))
    };
    m_window->draw(soundLine, 2, sf::Lines);
    m_sound.setType("SOUND: ");
    m_window->draw(m_sound.getType());
    m_window->draw(m_sound.getCircle());
    m_window->display();
}

void Setting::create() {
    readFile();
    sort();
    m_settingBoard.setSize(sf::Vector2f(m_window->getSize().x/2 ,m_window->getSize().y/10*9));
    m_settingBoard.setPosition(m_window->getSize().x/2, m_window->getSize().y/2);
    m_settingBoard.setOrigin(m_settingBoard.getSize().x/2, m_settingBoard.getSize().y/2);
    m_settingBoard.setFillColor(sf::Color(245,208,208));
    m_music.create(1,m_settingBoard.getPosition());
    m_sound.create(2,m_settingBoard.getPosition());

    for(int index = 0; index < TOP_FIVE; index++){
        m_topBoard[index].setSize(sf::Vector2f (m_music.getStart().x - m_music.getEnd().x, 80));
        m_topBoard[index].setPosition(sf::Vector2f(m_settingBoard.getPosition().x, m_settingBoard.getPosition().y + 80 * index)); //-position.y));
        m_topBoard[index].setOrigin(m_topBoard->getSize().x/2, m_topBoard->getSize().y/2);
        m_topBoard[index].setFillColor(sf::Color(245,222,222));
        m_topBoard[index].setOutlineThickness(2);
        m_topBoard[index].setOutlineColor(sf::Color(150,150,150));

        m_topText[index].setPosition(m_topBoard[index].getPosition().x, m_topBoard[index].getPosition().y - 15);
        m_topText[index].setOrigin(m_topText[index].getLocalBounds().width/2, m_topText[index].getLocalBounds().height/2);
        m_topText[index].setFillColor(sf::Color(150,150,150));
    }
    m_music.setType("MUSIC: ");
    m_sound.setType("SOUND: ");
}

Setting::~Setting() {
    writeFile();
}

void Setting::readFile() {
    std::ifstream readingFile;
    std::string filePath = "settingManager";
    if (!std::filesystem::exists(filePath)) { //Can't open a none existing file
        throw FileNotExist();
    }
    readingFile.open(filePath, std::fstream::in);
    if (!readingFile.is_open()) {             //File doesn't open
        throw OpenFileFailed();
    }
    int tempVol;
    readingFile >> tempVol;
    m_sound.setVolume(tempVol);
    readingFile >> tempVol;
    m_music.setVolume(tempVol);
    for(int index = 0; index < TOP_FIVE; index++){
        readingFile >> m_topScore[index];
    }
    readingFile.close();
}

void Setting::writeFile() {
    std::ofstream writingFile;
    std::string filePath = "settingManager";
    if (std::filesystem::exists(filePath)) {
        //If the file exist then we clear all the file contents and create a new empty file.
        writingFile.open(filePath, std::ios::out | std::ios::trunc);
    } else {
        writingFile.open(filePath);
    }
    if (!writingFile.is_open()) {
        throw OpenFileFailed();
    }
    m_music.positionToVolume();
    m_sound.positionToVolume();

    writingFile << m_sound.getVolume() << " " << m_music.getVolume() << "\n";
    for(int index = 0; index < TOP_FIVE; index++) {
        writingFile << m_topScore[index] << " ";
    }
    writingFile.close();
}

void Setting::sort() {
    for (int i = 0; i < TOP_FIVE - 1; i++) {
        for (int j = 0; j < TOP_FIVE - i - 1; j++) {
            if (m_topScore[j] < m_topScore[j + 1]) {
                // Swap the elements
                int temp = m_topScore[j];
                m_topScore[j] = m_topScore[j + 1];
                m_topScore[j + 1] = temp;
            }
        }
    }
    for(int i = 0; i < TOP_FIVE; i++){
        m_topText[i] = sf::Text(std::to_string(m_topScore[i]), ResourcesManager::instance().getFont(), 60);
    }
}

void Setting::checkPotentialBest(int score) {
    //sort();
    if (score > m_topScore[0]){
        m_topScore[0] = score;
        sort();
    }
}