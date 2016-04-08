#include "SFML/Audio.hpp" 
#include "cmath" 
#include "kf/kf_log.h" 
#include "qgf2d/system.h"
#include "qgf2d/anim.h"

#include <fstream>

#include "SpriteManager.h"
#include "GameStateManager.h"
#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Collision.h"

using namespace std; 
using namespace qgf; 
using namespace kf; 
using namespace sf; 

void Initialise()
{
	CreatePlayer();
	CreateEnemies();
}

void Update(RenderWindow &window, float deltaT)
{
	// Update player/enemy positions, deaths, etc.
	UpdatePlayer(window, deltaT);
	UpdateEnemies(deltaT);
	UpdateBullets(window, deltaT);
	m_worldCamera.UpdateCamera(deltaT);
	CheckCollision();
}

void Render(RenderWindow &window, bool &pauseMenu, bool &gameOver, Drawable &pScore, Drawable &hScore)
{
	// Draw everything to the screen:
	window.Clear();
	RenderPlayer(window);
	RenderEnemies(window);
	RenderBullets(window);
	window.Draw(pScore);
	window.Draw(hScore);
	if (pauseMenu)
	{
		window.Draw( SpriteManager::Get().GetPauseScreen() );
	}
	if (gameOver)
	{
		window.Draw( SpriteManager::Get().GetHighScoreScreen() );
	}
	window.Display();
}

void ResetGame()
{
	PlayerBullets.swap( BulletList() );
	m_player.isDead = false;
	m_player.enterGodMode = false;
	m_player.tenThousandCounter = 0;
	enemySpeed = 70;
	waveNumber = 0;
	increaseNumberOfEnemies = 0;
	difficultyCounter = 0;
	bulletTimerModifier = 0;
}

int main() 
{ 
    // This will initialise the QGF2D folders: 
    initDirectory(); 
	
    // Set up logging: 
    Log::getDefault().addCout(); 
    Log::getDefault().addFile("GeometryWars.log"); 
    kf_log("Geometry Wars: PLAY THIS GAME!!!");

	ShowCursor(false);

	// Input from external files:
	ifstream resolutionFile("data/resolution.txt");
	int screenWidth = 1280, screenHeight = 720;

	if ( !resolutionFile.fail() )
	{
		resolutionFile >> screenWidth;
		resolutionFile >> screenHeight;
	}

	ifstream highScoreFileRead("data/highScore.txt");
	int highScore;

	if ( !highScoreFileRead.fail() )
	{
		highScoreFileRead >> highScore;
	}

    // Set up window resolution and title: 
    RenderWindow window(VideoMode(screenWidth, screenHeight, 32), "Geometry Wars: Post TI3 where Na'Vi screwed the pooch");

    // Creating our sprite objects: 
	SpriteManager::Get().LoadSprites();


	// Create sound and sound buffer:
	sf::SoundBuffer gameMusicBuffer;
	sf::Sound gameMusic;
	if (!gameMusicBuffer.LoadFromFile("data/gamemusic.wav"))
		cout << "Game music file did not load!" << endl;
	sf::SoundBuffer highScoreMusicBuffer;
	sf::Sound highScoreMusic;
	if (!highScoreMusicBuffer.LoadFromFile("data/highscoremusic.wav"))
		cout << "High score music file did not load!" << endl;
	/*sf::SoundBuffer laserSoundBuffer;
	sf::Sound laserSound;
	if (!laserSoundBuffer.LoadFromFile("data/laser.wav"))
		cout << "Laser sound file did not load!" << endl;*/
	sf::SoundBuffer bombSoundBuffer;
	sf::Sound bombSound;
	if (!bombSoundBuffer.LoadFromFile("data/grenade.wav"))
		cout << "Explosion sound file did not load!" << endl;
	
	// Set the sound's buffer:
	gameMusic.SetBuffer(gameMusicBuffer);
	highScoreMusic.SetBuffer(highScoreMusicBuffer);
	//laserSound.SetBuffer(laserSoundBuffer);
	bombSound.SetBuffer(bombSoundBuffer);

	gameMusic.SetVolume(75);
	highScoreMusic.SetVolume(75);
	//laserSound.SetVolume(25);
	bombSound.SetVolume(200);

	bool pauseMenu = false;

	// Set game state to the title screen:
	stateStack.push(Title);

	while (window.IsOpened()) 
	{  
		Event ev; 
		while (window.GetEvent(ev)) 
		{ 
			if ((ev.Type == Event::Closed)) 
			{ 
			    window.Close(); 
			    break; 
			} 
		}
		
		// Text for score:
		std::stringstream scoreString;
		scoreString << "Your score: " << m_player.playerScore;
		char pStr[256];
		scoreString.getline(pStr, 256);
		String pScore;
		pScore.SetPosition(50, 50);
		pScore.SetText(pStr);
		pScore.SetSize(24);

		std::stringstream highScoreString;
		highScoreString << "High Score: " << highScore;
		char hStr[256];
		highScoreString.getline(hStr, 256);
		String hScore;
		hScore.SetPosition(1000, 50);
		hScore.SetText(hStr);
		hScore.SetSize(24);

		float deltaT = window.GetFrameTime();
		
		GameState currentState = stateStack.top();

		switch (currentState)
		{
		case Title:
			window.Clear();
			window.Draw( SpriteManager::Get().GetTitleScreen() );
			window.Display();

			gameMusic.Play();

			if (window.GetInput().IsKeyDown(Key::Return))
			{
				stateStack.push(Game);
				Initialise();
			}
			break;
		case Game:
			Update(window, deltaT);
			Render(window, pauseMenu, m_player.gameOver, pScore, hScore);

			PerformEnemyCheck();
			PerformTenThousandScoreCheck();

			// Play sounds:
			if (window.GetInput().IsKeyDown(Key::Space))
			{
				bombSound.Play();
			}

			// Replace high score if current score is higher:
			if (m_player.playerScore > highScore)
			{
				highScore = m_player.playerScore;
			}

			if (m_player.lives == 0)
			{
				m_player.gameOver = true;
				stateStack.push(HighScore);
				cout << "Game over, sucker!" << endl;
			}
			
			if (m_player.gameOver && (m_player.playerScore >= highScore))
			{
				gameMusic.Stop();
				highScoreMusic.Play();
			}

			// Access pause menu:
			if (window.GetInput().IsKeyDown(Key::Escape))
			{
				stateStack.push(Pause);
				pauseMenu = true;
			}
			break;
		case Pause:
			Render(window, pauseMenu, m_player.gameOver, pScore, hScore);
			if (window.GetInput().IsKeyDown(Key::Return))
			{
				stateStack.pop();
				pauseMenu = false;
			}
			break;
		case HighScore:
			Render(window, pauseMenu, m_player.gameOver, pScore, hScore);
			
			// Reset all the values for game restart:
			ResetGame();
			
			if (window.GetInput().IsKeyDown(Key::Space))
			{
				highScoreMusic.Stop();
				
				stateStack.pop();
				stateStack.pop();	// Activating Game State due to Enter press?
			}
			break;
		default:
			break;
		}
    }
	return 0; 
}