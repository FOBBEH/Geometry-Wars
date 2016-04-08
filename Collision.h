#ifndef COLLISION_H
#define COLLISION_H

#include <vector>

#include "SpriteManager.h"

// FUNCTIONS:
bool AreCirclesColliding(Vector2f circle1Pos, float circle1Rad, Vector2f circle2Pos, float circle2Rad);

void CheckCollision();

#endif // COLLISION_H