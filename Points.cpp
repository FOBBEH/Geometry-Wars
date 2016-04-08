#include "Points.h"

void DisplayPoints(RenderWindow &window, int points, sf::Vector2f deathPosition)
{
	std::stringstream pointsStream;
	pointsStream << points;
	char pStr[256];
	pointsStream.getline(pStr, 256);
	String pointsString;
	pointsString.SetPosition(deathPosition);
	pointsString.SetText(pStr);
	pointsString.SetSize(10);

	window.Draw(pointsString);
}