#ifndef OBJECT_H
#define OBJECT_H

// Class to be inhereted from:
struct Object
{
	sf::Vector2f worldPosition;
	float radius;
	bool isDead;
};

#endif // OBJECT_H