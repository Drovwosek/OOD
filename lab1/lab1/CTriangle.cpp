#include "CTriangle.h"

CTriangleShape::CTriangleShape(const sf::Vector2f& point1, const sf::Vector2f& point2, const sf::Vector2f& point3)
	: m_point1(point1), m_point2(point2), m_point3(point3) {}

double CTriangleShape::GetSquare() const
{
	double a = GetSide(m_point1, m_point2);
	double b = GetSide(m_point2, m_point3);
	double c = GetSide(m_point3, m_point1);

	double p = (a + b + c) / 2;
	return std::sqrt(p * (p - a) * (p - b) * (p - c)); 
}

double CTriangleShape::GetPerimeter() const
{
	double a = GetSide(m_point1, m_point2);
	double b = GetSide(m_point2, m_point3);
	double c = GetSide(m_point3, m_point1);

	return a + b + c;
}

sf::FloatRect CTriangleShape::GetBounds() const
{
	// Возвращаем ограничивающий прямоугольник для треугольника
	float left = std::min({ m_point1.x, m_point2.x, m_point3.x });
	float top = std::min({ m_point1.y, m_point2.y, m_point3.y });
	float right = std::max({ m_point1.x, m_point2.x, m_point3.x });
	float bottom = std::max({ m_point1.y, m_point2.y, m_point3.y });

	sf::FloatRect bounds(left, top, right - left, bottom - top);
	return bounds;
}

void CTriangleShape::Draw(sf::RenderWindow& window) const
{
	sf::ConvexShape triangle;
	triangle.setPointCount(3);
	triangle.setPoint(0, m_point1);
	triangle.setPoint(1, m_point2);
	triangle.setPoint(2, m_point3);
	triangle.setFillColor(sf::Color::Blue);
	window.draw(triangle);
}

std::string CTriangleShape::ToString() const
{
	std::stringstream ss;
	ss << "TRIANGLE: P=" << GetPerimeter() << "; S=" << GetSquare();
	return ss.str();
}

double CTriangleShape::GetSide(const sf::Vector2f& point1, const sf::Vector2f& point2) const
{
	double dx = point2.x - point1.x;
	double dy = point2.y - point1.y;
	return std::sqrt(dx * dx + dy * dy);
}