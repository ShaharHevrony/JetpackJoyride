#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

#include "Exeption.h"
#include "Values.h"

class GameManager {
public:
    static GameManager& instance();
    void readFile();
    void writeFile();
    void checkPotentialBest(int score);
    void sort();

    void setTopScore(int* top);
    int getTopScore(int index) const;
    int getBest () const;
    void setSound(int sound);
    float getSound() const;
    void setMusic(int music);
    int getMusic() const;
    void setCollectedSum(int collected);
    void setCollectedSumBuy(int price);
    int getCollectedSum() const;
    void setCharacter(int character);
    int getCharacter() const;
    bool getOwned(int index) const;
    void setOwned(int index);

private:
    GameManager();
    ~GameManager();

    int m_topScore[5];
    int m_musicVolume;
    int m_soundVolume;
    int m_collectedSum;
    int m_chosenCharacter;

    bool m_ownedGear[4] = {false};
};
