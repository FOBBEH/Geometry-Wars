#include "Player.h"
#include "Camera.h"
#include "Bullet.h"

#include <math.h>

Player m_player;
Camera m_worldCamera;

int godModeTimer = 1000;

void CreatePlayer()
{
	m_player.worldPosition.x = 640;
	m_player.worldPosition.y = 360;
	m_player.radius = 24.0f;
	m_player.playerScore = 0;
	m_player.lives = 3;
	m_player.bombs = 3;
	m_player.tenThousandCounter = 0;
	m_player.gameOver = false;
}

float GetLength(const sf::Vector2f &v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}

void Normalise(sf::Vector2f &v)
{
	// Get the length:
	float length = GetLength(v);

	// Reduce/increase our length to 1 unit long:
	if (length != 0.0f)
	{
		v.x /= length;
		v.y /= length;
	}
}

void UpdatePlayer(RenderWindow &window, float deltaT)
{
	float theta = atan2( (m_player.worldPosition.y - window.GetInput().GetMouseY() - m_worldCamera.cameraPosition.y), 
							(m_player.worldPosition.x - window.GetInput().GetMouseX() - m_worldCamera.cameraPosition.x) );

	if (m_player.enterGodMode)
	{
		--godModeTimer;
	}

	if (godModeTimer == 0)
	{
		godModeTimer = 1000;
		m_player.enterGodMode = false;
	}

	// Player can move left and right:
	if (window.GetInput().IsKeyDown(Key::W))
	{ 
		m_player.worldPosition.y -= 250 * deltaT;
		m_worldCamera.cameraPosition.y += 0.1f * deltaT;
	} 
	if (window.GetInput().IsKeyDown(Key::S))
	{ 
		m_player.worldPosition.y += 250 * deltaT;
		m_worldCamera.cameraPosition.y -= 0.1f * deltaT;
	} 
	if (window.GetInput().IsKeyDown(Key::A))
	{ 
		m_player.worldPosition.x -= 250 * deltaT;
		m_worldCamera.cameraPosition.x += 0.1f * deltaT;
	}
	if (window.GetInput().IsKeyDown(Key::D))
	{ 
		m_player.worldPosition.x += 250 * deltaT;
		m_worldCamera.cameraPosition.x -= 0.1f * deltaT;
	}

	// Set boundaries for the player: 
	if (m_player.worldPosition.x < 320.0f)
	{ 
		m_player.worldPosition.x = 320.0f;
			}
	if (m_player.worldPosition.x > 980.0f) 
	{ 
		m_player.worldPosition.x = 980.0f;
			}
	if (m_player.worldPosition.y < 0.0f)
	{ 
		m_player.worldPosition.y = 0.0f;
			}
	if (m_player.worldPosition.y > 720.0f) 
	{ 
		m_player.worldPosition.y = 720.0f;
	}

	SpriteManager::Get().GetBackground().SetPosition(m_worldCamera.cameraPosition.x+640, m_worldCamera.cameraPosition.y+360);
	SpriteManager::Get().GetMouse().SetPosition(window.GetInput().GetMouseX(), window.GetInput().GetMouseY());
	SpriteManager::Get().GetPlayer().SetPosition(m_player.worldPosition - m_worldCamera.cameraPosition);
	SpriteManager::Get().GetPlayer().SetRotation((-theta * 180 / 3.14f) + 90);
}

void RenderPlayer(RenderWindow &window)
{
	window.Draw( SpriteManager::Get().GetBackground() );
	window.Draw( SpriteManager::Get().GetMouse() );
	
	// Show the boundary:
	window.Draw( Shape::Rectangle(300-m_worldCamera.cameraPosition.x,740-m_worldCamera.cameraPosition.y,
									1000-m_worldCamera.cameraPosition.x,-20-m_worldCamera.cameraPosition.y,sf::Color(255,255,255,20)) );	// White transparent

	// Will fade for invulnerability status:
	if (godModeTimer % 5 == 0)
	{
		window.Draw( SpriteManager::Get().GetPlayer() );
	}

	// Life icons:
	for (int i = 0; i < m_player.lives; ++i)
	{
		SpriteManager::Get().GetLifeIcon().SetPosition(610 - (i * 40), 70);
		window.Draw( SpriteManager::Get().GetLifeIcon() );
	}
	// Bomb icons:
	for (int i = 0; i < m_player.bombs; ++i)
	{
		SpriteManager::Get().GetBombIcon().SetPosition(660 + (i * 40), 70);
		window.Draw( SpriteManager::Get().GetBombIcon() );
	}
}

void PerformTenThousandScoreCheck()
{
	// Every 10,000 points do stuff
	if (m_player.playerScore - (10000 * m_player.tenThousandCounter) > 10000)
	{
		++m_player.tenThousandCounter;
		bulletTimerModifier += 10;

		if (m_player.tenThousandCounter % 5 == 0 && m_player.tenThousandCounter != 0)
		{
			++m_player.lives;
			++m_player.bombs;
		}
	}
}