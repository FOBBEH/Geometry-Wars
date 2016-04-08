#ifndef BULLET_H
#define BULLET_H

#include <vector>

#include "SpriteManager.h"
#include "Object.h"

struct Bullet : public Object
{
	float thetaX;
	float thetaY;

	float bulletRotation;
};

// NEW VECTOR DEFINITION:
typedef std::vector<Bullet> BulletList;

extern BulletList PlayerBullets;

// FUNCTIONS:
extern int bulletTimerModifier;

void UpdateBullets(RenderWindow &window, float deltaT);
void RenderBullets(RenderWindow &window);

bool PlayerBulletOffScreen(Bullet bullet);
bool BulletIsDead(Bullet bullet);

#endif // BULLET_H