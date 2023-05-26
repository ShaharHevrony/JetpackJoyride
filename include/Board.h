#pragma once
#include <SFML/Graphics.hpp>
#include "Values.h"
#include "Coins.h"
#include "Player.h"

class Board {
public:
	Board() {};
	void craete();
	void draw();
private:
	Player m_player;
	Obstacle m_obstacle;
	Obstacle m_obstacleOpposite;
};
