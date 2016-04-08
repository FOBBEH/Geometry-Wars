#ifndef PLAYER_H
#define PLAYER_H

#include "SpriteManager.h"
#include "Object.h"

struct Player : public Object
{
	int playerScore;
	int lives;
	int bombs;
	int tenThousandCounter;
	bool enterGodMode;
	bool gameOver;
};

// OBJECT:
extern Player m_player;

// FUNCTIONS:
void CreatePlayer();

void UpdatePlayer(RenderWindow &window, float deltaT);
void RenderPlayer(RenderWindow &window);
void PerformTenThousandScoreCheck();

#endif // PLAYER_H