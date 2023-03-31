#ifndef JUDGEFUNCTIONS_H
#define JUDGEFUNCTIONS_H

#include<math.h>
#include<algorithm>

#include"SFML/Graphics.hpp"

class JudgeFunctions
{
public:
	static bool CircleandRectangle(sf::Vector2f rec_center, sf::Vector2f rec_size, sf::Vector2f cir_center, float cir_radius);
	static bool CircleandCircle(sf::Vector2f cir1_center, float cir1_radius, sf::Vector2f cir2_center, float cir2_radius);
	static bool CircleandPoint(sf::Vector2f cir_center, float cir_radius, sf::Vector2f point);
	static bool CircleandLine(sf::Vector2f cir_center, float cir_radius, sf::Vector2f point1, sf::Vector2f point2);

	static float CircleandLineVerticalLength(sf::Vector2f cir_center, float cir_radius, sf::Vector2f point1, sf::Vector2f point2);

	static float PointDistance(sf::Vector2f point1, sf::Vector2f point2);
};

#endif