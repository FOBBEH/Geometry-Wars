#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <stack>

enum GameState
{
	Title,
	Game,
	Pause,
	HighScore
};

stack<GameState> stateStack;

#endif // GAMESTATEMANAGER_H