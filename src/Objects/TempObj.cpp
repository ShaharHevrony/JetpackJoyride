#include "TempObj.h"

TempObj::TempObj(sf::Texture *texture, const sf::Vector2f &position) :Object(texture, position) {}

TempObj::~TempObj() {}

void TempObj::move(float time){
    sf::Vector2f direction(-1,0);
    m_object.move(direction*time/(2.f));
}
