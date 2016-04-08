#include <time.h>

#include "Enemy.h"
#include "Player.h"
#include "Points.h"
#include "Camera.h"
#include "Bullet.h"

EnemyList CompleteEnemyList;

const int tailSections = 5;
const float segmentLength = 30.0f;

const float greenSpeedPassiveModifier = 0.5f;
const float greenSpeedModifier = 2.5f;
const float purpleSpeedModifier = 1.7f;
const float snakeSpeedModifier = 1.4f;

int enemySpeed = 100;
int waveNumber = 0;
int increaseNumberOfEnemies = 0;
int difficultyCounter = 0;

bool purpleEnemyIsAlive = false;
int purpleEnemyRotation = 0;

float GetLength(Vector2f vector)
{
	// This is Pythag.
	return sqrtf( vector.x * vector.x + vector.y * vector.y );
}

sf::Vector2f Normalise(Vector2f vector)
{
	// Get the length:
	float length = GetLength(vector);

	// Reduce/increase our length to 1 unit long:
	if (length > 0)
	{
		vector.x = vector.x / length;
		vector.y = vector.y / length;
	}

	return vector;
}

void CreateEnemies()
{
	CompleteEnemyList.swap( EnemyList() );
	
	srand(time(NULL));

	int numberOfEnemies = rand() % 5 + (10 + increaseNumberOfEnemies);

	for (int i = 0; i < numberOfEnemies; ++i)
	{
		int decideEnemyType = rand() % 5;					// Decide what type of enemy will spawn
		
		// Random enemy spawns from player's position:
		int randomWorldPositionX = rand() % 400 + 200;		// Spawn at least 200 away from player
		int randomWorldPositionY = rand() % 400 + 200;

		if (randomWorldPositionX % 2)
			randomWorldPositionX *= -1;
		if (randomWorldPositionY % 2)
			randomWorldPositionY *= -1;

		sf::Vector2f randomWorldPosition;
		randomWorldPosition.x = randomWorldPositionX;
		randomWorldPosition.y = randomWorldPositionY;

		// Harder enemies as game progresses (difficultyCounter):
		if (difficultyCounter < 2)
		{
			Enemy blueEnemy;
			blueEnemy.worldPosition = m_player.worldPosition + randomWorldPosition;
			blueEnemy.radius = 20.0f;
			blueEnemy.isDead = false;
			blueEnemy.points = 250;
			CompleteEnemyList.push_back( blueEnemy );
		}
		else if (difficultyCounter < 4)
		{
			switch (decideEnemyType)
			{
			case 0:
				{
					Enemy greenEnemy;
					greenEnemy.worldPosition = m_player.worldPosition + randomWorldPosition;
					greenEnemy.radius = 15.0f;
					greenEnemy.isDead = false;
					greenEnemy.points = 300;
					CompleteEnemyList.push_back( greenEnemy );
					break;
				}
			default:
				{
					Enemy blueEnemy;
					blueEnemy.worldPosition = m_player.worldPosition + randomWorldPosition;
					blueEnemy.radius = 20.0f;
					blueEnemy.isDead = false;
					blueEnemy.points = 250;
					CompleteEnemyList.push_back( blueEnemy );
					break;
				}
			}
		}
		else if (difficultyCounter < 6)
		{
			switch (decideEnemyType)
			{
			case 0:
				{
					Enemy greenEnemy;
					greenEnemy.worldPosition = m_player.worldPosition + randomWorldPosition;
					greenEnemy.radius = 15.0f;
					greenEnemy.isDead = false;
					greenEnemy.points = 300;
					CompleteEnemyList.push_back( greenEnemy );
					break;
				}
			case 1:
				{
					Enemy purpleEnemy;
					purpleEnemy.worldPosition = m_player.worldPosition + randomWorldPosition;
					purpleEnemy.radius = 28.0f;
					purpleEnemy.isDead = false;
					purpleEnemy.points = 500;
					CompleteEnemyList.push_back( purpleEnemy );

					purpleEnemyIsAlive = true;
					break;
				}
			default:
				{
					Enemy blueEnemy;
					blueEnemy.worldPosition = m_player.worldPosition + randomWorldPosition;
					blueEnemy.radius = 20.0f;
					blueEnemy.isDead = false;
					blueEnemy.points = 250;
					CompleteEnemyList.push_back( blueEnemy );
					break;
				}
			}
		}
		else
		{
			switch (decideEnemyType)
			{
			case 0:
				{
					Enemy greenEnemy;
					greenEnemy.worldPosition = m_player.worldPosition + randomWorldPosition;
					greenEnemy.radius = 15.0f;
					greenEnemy.isDead = false;
					greenEnemy.points = 300;
					CompleteEnemyList.push_back( greenEnemy );
					break;
				}
			case 1:
				{
					Enemy purpleEnemy;
					purpleEnemy.worldPosition = m_player.worldPosition + randomWorldPosition;
					purpleEnemy.radius = 28.0f;
					purpleEnemy.isDead = false;
					purpleEnemy.points = 500;
					CompleteEnemyList.push_back( purpleEnemy );

					purpleEnemyIsAlive = true;
					break;
				}
			case 2:
				{
					// Snake head
					Enemy snakeEnemy;
					snakeEnemy.worldPosition = m_player.worldPosition + randomWorldPosition;
					snakeEnemy.radius = 24.0f;
					snakeEnemy.isDead = false;
					snakeEnemy.points = 700;
					CompleteEnemyList.push_back( snakeEnemy );

					// Tail sections
					for (int i = 0; i < tailSections; ++i)
					{
						Tail N0tail;
						N0tail.worldPosition = snakeEnemy.worldPosition;
						N0tail.radius = 16.0f;
						N0tail.isDead = false;
						N0tail.points = 600;
						CompleteEnemyList.push_back( N0tail );
					}
					break;
				}
			default:
				{
					Enemy blueEnemy;
					blueEnemy.worldPosition = m_player.worldPosition + randomWorldPosition;
					blueEnemy.radius = 20.0f;
					blueEnemy.isDead = false;
					blueEnemy.points = 250;
					CompleteEnemyList.push_back( blueEnemy );
					break;
				}
			}
		}
	}
}

void UpdateEnemies(float deltaT)
{
	// Enemies move towards the player
	for (int i = 0; i < CompleteEnemyList.size(); i++)
	{
		float theta = atan2( (m_player.worldPosition.y - CompleteEnemyList[i].worldPosition.y), 
							(m_player.worldPosition.x - CompleteEnemyList[i].worldPosition.x) );

		CompleteEnemyList[i].thetaX = sinf(theta + (3.14f/2));
		CompleteEnemyList[i].thetaY = -cosf(theta + (3.14f/2));

		if (purpleEnemyIsAlive)
		{
			++purpleEnemyRotation;
		}
		else
		{
			purpleEnemyIsAlive = false;
		}

		// Boundaries for the enemies:
		if (CompleteEnemyList[i].worldPosition.x < 320.0f)
		{ 
			CompleteEnemyList[i].worldPosition.x = 320.0f;
		}
		if (CompleteEnemyList[i].worldPosition.x > 980.0f) 
		{ 
			CompleteEnemyList[i].worldPosition.x = 980.0f;
		}
		if (CompleteEnemyList[i].worldPosition.y < 0.0f)
		{ 
			CompleteEnemyList[i].worldPosition.y = 0.0f;
		}
		if (CompleteEnemyList[i].worldPosition.y > 720.0f) 
		{ 
			CompleteEnemyList[i].worldPosition.y = 720.0f;
		}

		if (CompleteEnemyList[i].points == 250)				// Blue enemy: (identifying with points value)
		{
			CompleteEnemyList[i].worldPosition.x += (enemySpeed * CompleteEnemyList[i].thetaX) * deltaT;
			CompleteEnemyList[i].worldPosition.y += (enemySpeed * CompleteEnemyList[i].thetaY) * deltaT;
		}
		else if (CompleteEnemyList[i].points == 300)		// Green enemy:
		{
			float distance = GetLength(m_player.worldPosition - CompleteEnemyList[i].worldPosition);

			// Get away mode:
			if (distance < 200.f)
			{
				CompleteEnemyList[i].worldPosition.x -= ((enemySpeed*greenSpeedModifier) * CompleteEnemyList[i].thetaX) * deltaT;
				CompleteEnemyList[i].worldPosition.y -= ((enemySpeed*greenSpeedModifier) * CompleteEnemyList[i].thetaX) * deltaT;
			}
			// Passive mode:
			else
			{
				CompleteEnemyList[i].worldPosition.x += ((enemySpeed*greenSpeedPassiveModifier) * CompleteEnemyList[i].thetaX) * deltaT;
				CompleteEnemyList[i].worldPosition.y += ((enemySpeed*greenSpeedPassiveModifier) * CompleteEnemyList[i].thetaX) * deltaT;
			}
		}
		else if (CompleteEnemyList[i].points == 500)		// Purple enemy:
		{
			CompleteEnemyList[i].worldPosition.x += ((enemySpeed*purpleSpeedModifier) * CompleteEnemyList[i].thetaX) * deltaT;
			CompleteEnemyList[i].worldPosition.y += ((enemySpeed*purpleSpeedModifier) * CompleteEnemyList[i].thetaY) * deltaT;
		}
		else if (CompleteEnemyList[i].points == 700)		// Snake enemy (head):
		{
			CompleteEnemyList[i].worldPosition.x += ((enemySpeed*snakeSpeedModifier) * CompleteEnemyList[i].thetaX) * deltaT;
			CompleteEnemyList[i].worldPosition.y += ((enemySpeed*snakeSpeedModifier) * CompleteEnemyList[i].thetaY) * deltaT;
		}
		// Loop through the tails and update their positions:
		else if (CompleteEnemyList[i].points == 600)		// Snake enemy (tail):
		{
			// Follows the player if the previous head/tail is dead:
			if (CompleteEnemyList[i-1].isDead == true)
			{
				CompleteEnemyList[i].worldPosition.x += ((enemySpeed*snakeSpeedModifier) * CompleteEnemyList[i].thetaX) * deltaT;
				CompleteEnemyList[i].worldPosition.y += ((enemySpeed*snakeSpeedModifier) * CompleteEnemyList[i].thetaY) * deltaT;
			}
			else
			{
				sf::Vector2f previousGuysPosition = CompleteEnemyList[i-1].worldPosition;

				// Calculate distance between us and previous guy:
				float distance = GetLength(previousGuysPosition - CompleteEnemyList[i].worldPosition);

				// Move us closer if too far away:
				if (distance > segmentLength)
				{
					sf::Vector2f vecFromParentToMe = CompleteEnemyList[i].worldPosition - previousGuysPosition;
					vecFromParentToMe = Normalise(vecFromParentToMe);

					CompleteEnemyList[i].worldPosition = previousGuysPosition + vecFromParentToMe * segmentLength;
				}
			}
		}
	}
}

void RenderEnemies(RenderWindow &window)
{
	for (int i = 0; i < CompleteEnemyList.size(); ++i)
	{
		// Draw if enemy is alive:
		if (!CompleteEnemyList[i].isDead && CompleteEnemyList[i].points == 250)
		{
			SpriteManager::Get().GetBlueEnemy().SetPosition( CompleteEnemyList[i].worldPosition - m_worldCamera.cameraPosition);
			window.Draw( SpriteManager::Get().GetBlueEnemy() );
		}
		else if (!CompleteEnemyList[i].isDead && CompleteEnemyList[i].points == 300)
		{
			SpriteManager::Get().GetGreenEnemy().SetPosition( CompleteEnemyList[i].worldPosition - m_worldCamera.cameraPosition);
			window.Draw( SpriteManager::Get().GetGreenEnemy() );
		}
		else if (!CompleteEnemyList[i].isDead && CompleteEnemyList[i].points == 500)
		{
			SpriteManager::Get().GetPurpleEnemy().SetPosition( CompleteEnemyList[i].worldPosition - m_worldCamera.cameraPosition);
			
			// Rotate to spin around
			SpriteManager::Get().GetPurpleEnemy().SetRotation( purpleEnemyRotation );
			window.Draw( SpriteManager::Get().GetPurpleEnemy() );
		}
		else if (!CompleteEnemyList[i].isDead && CompleteEnemyList[i].points == 700)
		{
			float theta = atan2( (CompleteEnemyList[i].worldPosition.y - m_player.worldPosition.y), 
							(CompleteEnemyList[i].worldPosition.x - m_player.worldPosition.x) );
			
			SpriteManager::Get().GetSnakeEnemy().SetPosition( CompleteEnemyList[i].worldPosition - m_worldCamera.cameraPosition);
			
			// Rotate head to follow the player:
			SpriteManager::Get().GetSnakeEnemy().SetRotation((-theta * 180 / 3.14f) + 90);
			window.Draw( SpriteManager::Get().GetSnakeEnemy() );
		}
		else if (!CompleteEnemyList[i].isDead && CompleteEnemyList[i].points == 600)
		{
			SpriteManager::Get().GetSnakeEnemy().SetPosition( CompleteEnemyList[i].worldPosition - m_worldCamera.cameraPosition);

			// Rotate tail to follow player if head is dead:
			if (CompleteEnemyList[i-1].isDead)
			{
				float theta = atan2( (CompleteEnemyList[i].worldPosition.y - m_player.worldPosition.y), 
							(CompleteEnemyList[i].worldPosition.x - m_player.worldPosition.x) );

				SpriteManager::Get().GetSnakeEnemy().SetRotation((-theta * 180 / 3.14f) + 90);
				window.Draw( SpriteManager::Get().GetSnakeEnemy() );
			}
			// Rotate tail to follow the head/tail:
			else
			{
				float theta = atan2( (CompleteEnemyList[i].worldPosition.y - CompleteEnemyList[i-1].worldPosition.y), 
								(CompleteEnemyList[i].worldPosition.x - CompleteEnemyList[i-1].worldPosition.x) );

				// Rotate tails segments to follow each other:
				SpriteManager::Get().GetSnakeEnemy().SetRotation((-theta * 180 / 3.14f) + 90);
				window.Draw( SpriteManager::Get().GetSnakeEnemy() );
			}
		}
		else
		{
			// Show points when enemy dies:
			sf::Vector2f deathPosition = CompleteEnemyList[i].worldDeath - m_worldCamera.cameraPosition;

			DisplayPoints(window, CompleteEnemyList[i].points, deathPosition);
		}
	}
}

bool AllEnemiesDead(EnemyList CompleteEnemyList)
{
	for (int i = 0; i < CompleteEnemyList.size(); ++i)
	{
		if (!CompleteEnemyList[i].isDead)
		{
			return false;
		}
	}
	return true;
}

void PerformEnemyCheck()
{
	if ( AllEnemiesDead(CompleteEnemyList) )
	{
		++waveNumber;
		CreateEnemies();

		if ((waveNumber % 3 == 0) && (waveNumber != 0))
		{
			++increaseNumberOfEnemies;
			++difficultyCounter;
			enemySpeed += 10;
		}
	}
}