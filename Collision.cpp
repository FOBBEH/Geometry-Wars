#include <iostream>

#include "Collision.h"
#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

using std::cout;
using std::endl;

// Circle collision:
bool AreCirclesColliding(Vector2f circle1Pos, float circle1Rad, Vector2f circle2Pos, float circle2Rad)
{
	float distance = GetLength(circle1Pos - circle2Pos);
	float distanceBetween = distance - circle1Rad - circle2Rad;

	return (distanceBetween <= 0);
}

void CheckCollision()
{
	// Check if player bullets collide with any enemies:
	for (int k = 0; k < PlayerBullets.size(); ++k)
	{
		for (int i = 0; i < CompleteEnemyList.size(); ++i)
		{
			if (AreCirclesColliding( PlayerBullets[k].worldPosition, PlayerBullets[k].radius, 
									CompleteEnemyList[i].worldPosition - m_worldCamera.cameraPosition, CompleteEnemyList[i].radius ))
			{
				if (!CompleteEnemyList[i].isDead)
				{
					CompleteEnemyList[i].isDead = true;
					PlayerBullets[k].isDead = true;
					m_player.playerScore += CompleteEnemyList[i].points;
					CompleteEnemyList[i].worldDeath = CompleteEnemyList[i].worldPosition;
					cout << "Enemy is destroyed!" << endl;
				}
			}
		}
	}

	// Check if enemies collide with the player:
	for (int i = 0; i < CompleteEnemyList.size(); ++i)
	{
		if (AreCirclesColliding( m_player.worldPosition - m_worldCamera.cameraPosition, m_player.radius,
								CompleteEnemyList[i].worldPosition - m_worldCamera.cameraPosition, CompleteEnemyList[i].radius ))
		{
			if (!m_player.isDead && !CompleteEnemyList[i].isDead && !m_player.enterGodMode)
			{
				--m_player.lives;
				m_player.enterGodMode = true;
				cout << "Enemy collided with you!" << endl;
				if (m_player.lives == 0)
				{
					m_player.isDead = true;
					cout << "No more lives!" << endl;
				}
			}
		}
	}
}