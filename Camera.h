#ifndef CAMERA_H
#define CAMERA_H

#include "Player.h"

struct Camera
{
	sf::Vector2f cameraPosition;

	void UpdateCamera(float deltaT);
};

extern Camera m_worldCamera;

sf::Vector2f Lerp(sf::Vector2f a, sf::Vector2f b, float alpha);

#endif // CAMERA_H