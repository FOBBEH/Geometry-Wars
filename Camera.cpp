#include "Camera.h"
#include "Player.h"

// Brings player back to the centre:
sf::Vector2f Lerp(sf::Vector2f a, sf::Vector2f b, float alpha)
{
	return (a + (b-a) * alpha);
}

int SetCamera()
{
	Camera m_worldCamera;
	
	m_worldCamera.cameraPosition.x = 0;
	m_worldCamera.cameraPosition.y = 0;

	return 0;
}

void Camera::UpdateCamera(float deltaT)
{
	m_worldCamera.cameraPosition = Lerp(
		m_worldCamera.cameraPosition, m_player.worldPosition - sf::Vector2f(1280/2, 720/2), deltaT * 10.0f);
}