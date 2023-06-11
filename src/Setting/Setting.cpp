
#include "Setting.h"

Setting::Setting(sf::RenderWindow &window):m_window(&window) {}

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
                        else if (m_backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
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
    //FIXME: Add background below the overlay.
    m_overlay.setFillColor(sf::Color(0, 0, 0, 128));  // Semi-transparent black overlay
    m_window->draw(m_overlay);
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

    m_window->draw(m_backButton);
    m_window->draw(m_backText);

    m_window->display();
}

void Setting::create() {
    readFile();
    sort();
    int music = 1;
    int sound = 2;
    m_overlay = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_settingBoard.setSize(sf::Vector2f(SETTING_WIDTH ,SETTING_HEIGHT));
    m_settingBoard.setPosition(WIDTH_CENTER, HEIGHT_CENTER);
    m_settingBoard.setOrigin(SETTING_WIDTH/2, SETTING_HEIGHT/2);
    m_settingBoard.setFillColor(sf::Color(245,208,208));
    m_music.create(music);
    m_sound.create(sound);

    for(int index = 0; index < TOP_FIVE; index++){
        m_topBoard[index].setSize(sf::Vector2f (m_music.getStart().x - m_music.getEnd().x, SETTING_SIZE * 1.5));
        m_topBoard[index].setPosition(sf::Vector2f(WIDTH_CENTER, HEIGHT_CENTER + SETTING_SIZE * 1.5 * index)); //-position.y));
        m_topBoard[index].setOrigin(m_topBoard->getSize().x/2, m_topBoard->getSize().y/2);
        m_topBoard[index].setFillColor(sf::Color(245,222,222));
        m_topBoard[index].setOutlineThickness(2);
        m_topBoard[index].setOutlineColor(sf::Color(150,150,150));

        m_topText[index].setPosition(m_topBoard[index].getPosition().x, m_topBoard[index].getPosition().y - SETTING_SIZE/5);
        m_topText[index].setOrigin(m_topText[index].getLocalBounds().width/2, m_topText[index].getLocalBounds().height/2);
        m_topText[index].setFillColor(sf::Color(150,150,150));
    }
    m_music.setType("MUSIC: ");
    m_sound.setType("SOUND: ");

    m_backButton.setSize(sf::Vector2f(SETTING_SIZE * 2, SETTING_SIZE));
    //m_backButton.setPosition(sf::Vector2f(m_settingBoard.getPosition().x , m_settingBoard.getPosition().y));
    m_backButton.setPosition(WIDTH_CENTER, HEIGHT_CENTER);
    m_backButton.setOrigin(SETTING_WIDTH / 2, SETTING_HEIGHT / 2);

    m_backButton.setFillColor(sf::Color(200, 200, 200));
    m_backButton.setOutlineThickness(2);
    m_backButton.setOutlineColor(sf::Color(150, 150, 150));
    
    m_backText.setString("Back");
    m_backText.setFont(ResourcesManager::instance().getFont());
    //m_backText.setCharacterSize(FONT_SIZE);
    m_backText.setPosition(m_backButton.getPosition());
    m_backText.setOrigin(SETTING_WIDTH / 2 - SETTING_CIRCLE, SETTING_HEIGHT / 2 - SETTING_CIRCLE);
    //m_backText.setOrigin(m_backButton.getSize().x/2 , m_backButton.getSize().y/2);

    m_backText.setFillColor(sf::Color::Black);

}

Setting::~Setting() {
    writeFile();
}

void Setting::readFile() {
    std::ifstream readingFile;
    std::string filePath = "settingManager";
    if (!std::filesystem::exists(filePath)) { //Can't open a none existing file
        writeFile();
        if (!std::filesystem::exists(filePath)) { //Can't open a none existing file
            throw FileNotExist();
        }
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
        m_topText[i] = sf::Text(std::to_string(m_topScore[i]), ResourcesManager::instance().getFont(), SETTING_SIZE);
    }
}

void Setting::checkPotentialBest(int score) {
    //sort();
    if (score > m_topScore[0]){
        m_topScore[0] = score;
        sort();
    }
}
int Setting::getVol() {
    return m_music.getVolume();
}