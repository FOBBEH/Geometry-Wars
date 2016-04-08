#ifndef ENEMY_H
#define ENEMY_H

#include <vector>

#include "SpriteManager.h"
#include "Object.h"

struct Enemy : public Object
{
	Vector2f worldDeath;
	
	int points;
	
	float thetaX;
	float thetaY;
};

struct Tail : public Enemy
{
	// wut do?
};

// NEW VECTOR DEFINITION:
typedef std::vector<Enemy> EnemyList;

extern EnemyList CompleteEnemyList;

// VARIABLES:
extern int enemySpeed;
extern int waveNumber;
extern int increaseNumberOfEnemies;
extern int difficultyCounter;

// FUNCTIONS:
float GetLength(Vector2f vector);
sf::Vector2f Normalize(Vector2f vector);

void CreateEnemies();
void UpdateEnemies(float deltaT);
void RenderEnemies(RenderWindow &window);

bool AllEnemiesDead(EnemyList CompleteEnemyList);
void PerformEnemyCheck();

#endif // ENEMY_H