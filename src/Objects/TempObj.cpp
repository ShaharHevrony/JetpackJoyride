#include "TempObj.h"
#include "Coins.h"
TempObj::TempObj(sf::Texture *texture, const sf::Vector2f &position) :Object(texture, position) {}

TempObj::~TempObj() {}

void TempObj::move(float time){
    sf::Vector2f direction(-1,0);
    m_object.move(direction*time/(2.f));
}

void temp(){
    std::vector<std::vector<sf::Vector2f>> positions;
    std::vector<std::vector<Coins>> coins;
    sf::Texture* tex;
    int ROW = 15;
    int COL = 15;
    for(int row = 0; row < ROW; row++){
        std::vector<Coins> tempVec;
        for(int col = 0; col < COL; col++){
            Coins tempCoin = Coins(tex, positions[row][col]);
            tempVec.push_back(tempCoin);
        }
        coins.push_back(tempVec);
    }
}