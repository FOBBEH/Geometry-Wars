#include <iostream>
#include <cstdlib>

#include "SpriteManager.h"

SpriteManager *SpriteManager::m_theInstance = NULL;

SpriteManager &SpriteManager::Get()
{
	if (m_theInstance == NULL)
	{
		m_theInstance = new SpriteManager;
	}

	return *m_theInstance;
}

void SpriteManager::Destroy()
{
	delete m_theInstance;
	m_theInstance = NULL;
}

int SpriteManager::LoadSprites()
{
	// Prepare our images:
	if (!backgroundImage.LoadFromFile ("data/background.jpg"))
		cout << "Background image did not load!" << endl;
	if (!geometryWars.LoadFromFile ("data/geometryWars.png"))
		cout << "Geometry Wars image did not load!" << endl;
	if (!screens.LoadFromFile ("data/screens.png"))
		cout << "Screens image did not load!" << endl;

	// Set the sprites to the images:
	background		= backgroundImage;
	lifeIcon		= geometryWars;
	bombIcon		= geometryWars;
	mouse			= geometryWars;
	player			= geometryWars;
	playerBullet	= geometryWars;
	blueEnemy		= geometryWars;
	greenEnemy		= geometryWars;
	purpleEnemy		= geometryWars;
	snakeEnemy		= geometryWars;
	enemyBullet		= geometryWars;
	titleScreen		= screens;
	pauseScreen		= screens;
	highScoreScreen = screens;

	background.SetSubRect(IntRect(0,0,1920,1440));
	background.SetCenter(960,720);

	lifeIcon.SetSubRect(IntRect(128,0,192,64));
	lifeIcon.SetCenter(32,32);

	bombIcon.SetSubRect(IntRect(192,0,256,64));
	bombIcon.SetCenter(32,32);

	mouse.SetSubRect(IntRect(64,0,128,64));
	mouse.SetCenter(32,32);

	player.SetSubRect(IntRect(0,0,64,64));				// Co-ordinates to select sprite TOP LEFT, BOTTOM RIGHT
	player.SetCenter(32,32);							// Co-ordinates to set the center of the sprite

	playerBullet.SetSubRect(IntRect(0,128,64,192)); 
	playerBullet.SetCenter(32, 32); 

	blueEnemy.SetSubRect(IntRect(0,64,64,128));
	blueEnemy.SetCenter(32,32);

	greenEnemy.SetSubRect(IntRect(64,64,128,128));
	greenEnemy.SetCenter(32,32);

	purpleEnemy.SetSubRect(IntRect(128,64,192,128));
	purpleEnemy.SetCenter(32,32);

	snakeEnemy.SetSubRect(IntRect(192,64,256,128));
	snakeEnemy.SetCenter(32,32);

	enemyBullet.SetSubRect(IntRect(64,128,128,192));
	enemyBullet.SetCenter(32,32);

	titleScreen.SetSubRect(IntRect(0,0,1280,720));
	titleScreen.SetCenter(0,0);

	pauseScreen.SetSubRect(IntRect(0,720,1280,1440));
	pauseScreen.SetCenter(0,0);

	highScoreScreen.SetSubRect(IntRect(0,1440, 1280, 2160));
	highScoreScreen.SetCenter(0,0);

	return EXIT_SUCCESS;
}