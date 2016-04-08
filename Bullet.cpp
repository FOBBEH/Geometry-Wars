#include "Bullet.h"
#include "Camera.h"
#include "Player.h"
#include "Enemy.h"

BulletList PlayerBullets;

bool bulletCanBeFired = true;
bool bulletSprayCanBeFired = true;
bool bombCanBeFired = true;

int bulletTimer = 250;
int bulletTimerModifier = 0;
int bulletSprayTimer = 2000;
int bombTimer = 500;

void UpdateBullets(RenderWindow &window, float deltaT)
{
	float theta = atan2( (m_player.worldPosition.y - window.GetInput().GetMouseY() - m_worldCamera.cameraPosition.y), 
							(m_player.worldPosition.x - window.GetInput().GetMouseX() - m_worldCamera.cameraPosition.x) );

	// Left-click: Normal bullet
	if ( window.GetInput().IsMouseButtonDown(Mouse::Left) && 
		(bulletTimer == 250 - bulletTimerModifier) && bulletCanBeFired )
	{
		Bullet playerBullet;
		playerBullet.worldPosition = m_player.worldPosition - m_worldCamera.cameraPosition;
		playerBullet.radius = 5.0f;
		playerBullet.isDead = false;
		playerBullet.thetaX = sinf(theta + (3.14f/2));
		playerBullet.thetaY = -cosf(theta + (3.14f/2));
		playerBullet.bulletRotation = (-theta * 180 / 3.14f) + 90;

		bulletCanBeFired = false;

		PlayerBullets.push_back(playerBullet);
	}

	// Right-click: Spray bullet
	if ( window.GetInput().IsMouseButtonDown(Mouse::Right) && 
		bulletSprayTimer == 2000 && bulletSprayCanBeFired )
	{
		int bulletSprayNumber = 15;

		for (int i = 0; i < bulletSprayNumber; ++i)
		{
			Bullet playerBullet;
			playerBullet.worldPosition = m_player.worldPosition - m_worldCamera.cameraPosition;
			playerBullet.radius = 5.0f;
			playerBullet.isDead = false;
			playerBullet.thetaX = sinf( theta - (5 * (i * 5)) + (3.14f/4) );
			playerBullet.thetaY = -cosf( theta - (5 * (i * 5)) + (3.14f/4) );
			playerBullet.bulletRotation = (-theta * 180 / 3.14f) + 135;

			bulletSprayCanBeFired = false;

			PlayerBullets.push_back(playerBullet);
		}
	}

	// Space: Bomb
	if ( window.GetInput().IsKeyDown(Key::Space) && 
		m_player.bombs > 0 && bombTimer == 500)
	{ 
		int bombSegments = 71;
		
		for (int i = 0; i < bombSegments; ++i)		// Perfect number for full circle (trial and error)
		{
			Bullet playerBullet;
			playerBullet.worldPosition = m_player.worldPosition - m_worldCamera.cameraPosition;
			playerBullet.radius = 5.0f;
			playerBullet.isDead = false;
			playerBullet.thetaX = sinf(theta - (30 * (i * 20)) + (3.14f/2));
			playerBullet.thetaY = -cosf(theta - (30 * (i * 20)) + (3.14f/2));
			playerBullet.bulletRotation = (-theta * 180 / 3.14f) + 90;

			bombCanBeFired = false;

			PlayerBullets.push_back(playerBullet);
		}
		--m_player.bombs;
	}

	// Countdown the timers:
	if (!bulletCanBeFired)
	{
		--bulletTimer;
	}
	if (!bulletSprayCanBeFired)
	{
		--bulletSprayTimer;
	}
	if (!bombCanBeFired)
	{
		--bombTimer;
	}

	// Reset timers so bullets can be fired:
	if (bulletTimer == 0)
	{
		bulletTimer = 250 - bulletTimerModifier;
		bulletCanBeFired = true;
	}
	if (bulletSprayTimer == 0)
	{
		bulletSprayTimer = 2000;
		bulletSprayCanBeFired = true;
	}
	if (bombTimer == 0)
	{
		bombTimer = 500;
		bombCanBeFired = true;
	}

	// Screws up sometimes with bulletTimerModifier
	if ( (bulletCanBeFired && (bulletTimer != 250 - bulletTimerModifier)) ||
		(!bulletCanBeFired && bulletTimer < 0) )
	{
		bulletTimer = 250 - bulletTimerModifier;
	}

	// Remove bullets if off-screen or dead:
	PlayerBullets.erase(std::remove_if(PlayerBullets.begin(), PlayerBullets.end(), PlayerBulletOffScreen), PlayerBullets.end());
	PlayerBullets.erase(std::remove_if(PlayerBullets.begin(), PlayerBullets.end(), BulletIsDead), PlayerBullets.end());
	
	for (int i = 0; i < PlayerBullets.size(); ++i)
	{
		PlayerBullets[i].worldPosition.x -= (600 * PlayerBullets[i].thetaX) * deltaT;
		PlayerBullets[i].worldPosition.y -= (600 * PlayerBullets[i].thetaY) * deltaT;
	}
}

void RenderBullets(RenderWindow &window)
{
	for (int i = 0; i < PlayerBullets.size(); ++i)
	{
		SpriteManager::Get().GetPlayerBullet().SetRotation( PlayerBullets[i].bulletRotation );
		SpriteManager::Get().GetPlayerBullet().SetPosition( PlayerBullets[i].worldPosition );
		window.Draw( SpriteManager::Get().GetPlayerBullet() );
	}
}

bool PlayerBulletOffScreen(Bullet bullet)
{
	if (bullet.worldPosition.y <= 0)		return true;
	if (bullet.worldPosition.y >= 720)		return true;
	if (bullet.worldPosition.x <= 0)		return true;
	if (bullet.worldPosition.x >= 1280)		return true;
	else									return false;
}

bool BulletIsDead(Bullet bullet)
{
	return (bullet.isDead);
}