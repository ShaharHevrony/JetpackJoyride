#pragma once
#include <SFML/Graphics.hpp>
#include "ResourcesManager.h"
#include "GameManager.h"

class AudioManager {
public:
    AudioManager();
    ~AudioManager();
    void create(int index);
    float positionToVolume();
    void volumeToPosition();
    void handleMouseMoved(sf::Vector2f& mouseMove);

    sf::Vector2f getStart() const;
    sf::Vector2f getEnd() const;
    sf::Text getType() const;
    void setType(std::string string);
    int getVolume() const;
    void setVolume(int volume);
    sf::CircleShape getCircle() const;
    void setGrabbed(bool grabbed);

private:
    int m_volume = 0;
    sf::Vector2f m_start;
    sf::Vector2f m_end;
    sf::CircleShape m_circle;
    bool m_grabbed;
    sf::Text m_type;
};
