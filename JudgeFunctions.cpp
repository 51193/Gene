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

bool JudgeFunctions::LineandLine(sf::Vector2f point1_1, sf::Vector2f point1_2, sf::Vector2f point2_1, sf::Vector2f point2_2)
{
	if (std::max(point2_1.x, point2_2.x) < std::min(point1_1.x, point1_2.x) ||
		std::max(point1_1.x, point1_2.x) < std::min(point2_1.x, point2_2.x) ||
		std::max(point2_1.y, point2_2.y) < std::min(point1_1.y, point1_2.y) ||
		std::max(point1_1.y, point1_2.y) < std::min(point2_1.y, point2_2.y))
	{
		return false;
	}
	else if (
		JudgeFunctions::Cross(point1_1 - point2_2, point2_1 - point2_2) *
		JudgeFunctions::Cross(point1_2 - point2_2, point2_1 - point2_2) > 0 ||
		JudgeFunctions::Cross(point2_2 - point1_2, point1_1 - point1_2) *
		JudgeFunctions::Cross(point2_1 - point1_2, point1_1 - point1_2) > 0) 
	{
		return false;
	}
	else 
	{
		return true;
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

sf::Vector2f JudgeFunctions::LineandLineIntersectionPoint(sf::Vector2f point1_1, sf::Vector2f point1_2, sf::Vector2f point2_1, sf::Vector2f point2_2)
{
	float k1 = (point1_1.y - point1_2.y) / (point1_1.x - point1_2.x);
	float k2 = (point2_1.y - point2_2.y) / (point2_1.x - point2_2.x);

	float x1 = point1_1.x;
	float y1 = point1_1.y;

	float x2 = point1_2.x;
	float y2 = point1_2.y;

	float x3 = point2_1.x;
	float y3 = point2_1.y;

	float x4 = point2_2.x;
	float y4 = point2_2.y;

	float x = (y3 - y1 + (y1 - y2) / (x1 - x2) * x1 - (y3 - y4) / (x3 - x4) * x3) / ((y1 - y2) / (x1 - x2) - (y3 - y4) / (x3 - x4));
	float y = y1 + (x - x1) * (y1 - y2) / (x1 - x2);

	return sf::Vector2f(x, y);
}

float JudgeFunctions::PointDistance(sf::Vector2f point1, sf::Vector2f point2)
{
	return sqrtf((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
}

float JudgeFunctions::Cross(sf::Vector2f point1, sf::Vector2f point2)
{
	return point1.x * point2.y - point2.x * point1.y;
}
