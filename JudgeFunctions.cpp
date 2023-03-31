#include "JudgeFunctions.h"

bool JudgeFunctions::CircleandRectangle(sf::Vector2f rec_center, sf::Vector2f rec_size, sf::Vector2f cir_center, float cir_radius)
{
	cir_center = cir_center - rec_center;
	cir_center = sf::Vector2f(abs(cir_center.x), abs(cir_center.y));

	sf::Vector2f upperright_point(rec_size.x / 2.f, rec_size.y / 2.f);

	sf::Vector2f temp = cir_center - upperright_point;
	temp = sf::Vector2f(std::max(temp.x, 0.f), std::max(temp.y, 0.f));

	if (temp.x * temp.x + temp.y * temp.y <= cir_radius) {
		return true;
	}
	return false;
}

bool JudgeFunctions::CircleandCircle(sf::Vector2f cir1_center, float cir1_radius, sf::Vector2f cir2_center, float cir2_radius)
{
	float temp1 = (cir1_center.x - cir2_center.x) * (cir1_center.x - cir2_center.x) + (cir1_center.y - cir2_center.y) * (cir1_center.y - cir2_center.y);
	float temp2 = (cir1_radius + cir2_radius) * (cir1_radius + cir2_radius);
	if (temp1 <= temp2) {
		return true;
	}
	return false;
}

bool JudgeFunctions::CircleandPoint(sf::Vector2f cir_center, float cir_radius, sf::Vector2f point)
{
	sf::Vector2f temp = cir_center - point;
	if (temp.x * temp.x + temp.y * temp.y <= cir_radius * cir_radius) {
		return true;
	}
	return false;
}

bool JudgeFunctions::CircleandLine(sf::Vector2f cir_center, float cir_radius, sf::Vector2f point1, sf::Vector2f point2)
{
	if (JudgeFunctions::PointDistance(point1, point2) < 0.01) {
		return false;
	}

	float x = JudgeFunctions::PointDistance(cir_center, point1);
	float y = JudgeFunctions::PointDistance(cir_center, point2);

	float z = JudgeFunctions::PointDistance(point1, point2);

	if (x <= cir_radius || y <= cir_radius) {
		return true;
	}
	else {
		if (x * x + y * y < z * z) {

			if (JudgeFunctions::CircleandLineVerticalLength(cir_center, cir_radius, point1, point2) < cir_radius) {
				return true;
			}
			return false;
		}
		else {
			if (std::min(x, y) < cir_radius) {
				return true;
			}
			return false;
		}
	}
}

float JudgeFunctions::CircleandLineVerticalLength(sf::Vector2f cir_center, float cir_radius, sf::Vector2f point1, sf::Vector2f point2)
{
	point1 -= cir_center;
	point2 -= cir_center;

	float k = -(point1.x * (point2.x - point1.x) + point1.y * (point2.y - point1.y)) / ((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
	sf::Vector2f X{ k * (point2.x - point1.x) + point1.x, k * (point2.y - point1.y) + point1.y };

	return JudgeFunctions::PointDistance(X, sf::Vector2f(0.f, 0.f));
}

float JudgeFunctions::PointDistance(sf::Vector2f point1, sf::Vector2f point2)
{
	return sqrtf((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
}
