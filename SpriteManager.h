// SpriteManager.h

#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class SpriteManager
{
public:
	static SpriteManager &	Get();
	static void				Destroy();

	int						LoadSprites();

	Sprite &				GetBackground()			{ return background; }
	Sprite &				GetLifeIcon()			{ return lifeIcon; }
	Sprite &				GetBombIcon()			{ return bombIcon; }
	Sprite &				GetMouse()				{ return mouse; }
	Sprite &				GetPlayer()				{ return player; }
	Sprite &				GetPlayerBullet()		{ return playerBullet; }
	Sprite &				GetBlueEnemy()			{ return blueEnemy; }
	Sprite &				GetGreenEnemy()			{ return greenEnemy; }
	Sprite &				GetPurpleEnemy()		{ return purpleEnemy; }
	Sprite &				GetSnakeEnemy()			{ return snakeEnemy; }
	Sprite &				GetEnemyBullet()		{ return enemyBullet; }
	Sprite &				GetTitleScreen()		{ return titleScreen; }
	Sprite &				GetPauseScreen()		{ return pauseScreen; }
	Sprite &				GetHighScoreScreen()	{ return highScoreScreen; }

private:
	static SpriteManager *	m_theInstance;

	SpriteManager() {}
	~SpriteManager() {}

	Image					backgroundImage;
	Image					geometryWars;
	Image					spaceInvaders;
	Image					screens;

	Sprite					background;
	Sprite					lifeIcon;
	Sprite					bombIcon;
	Sprite					mouse;
	Sprite					player;
	Sprite					playerBullet;
	Sprite					blueEnemy;
	Sprite					greenEnemy;
	Sprite					purpleEnemy;
	Sprite					snakeEnemy;
	Sprite					enemyBullet;
	Sprite					titleScreen;
	Sprite					pauseScreen;
	Sprite					highScoreScreen;
};

#endif // SPRITEMANAGER_H