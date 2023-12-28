#include "CTriangle.h"

CTriangleShape::CTriangleShape(const sf::Vector2f& point1, const sf::Vector2f& point2, const sf::Vector2f& point3)
	: m_point1(point1), m_point2(point2), m_point3(point3) {}

float CTriangleShape::GetSquare() const
{
	float a = GetSide(m_point1, m_point2);
	float b = GetSide(m_point2, m_point3);
	float c = GetSide(m_point3, m_point1);

	float p = (a + b + c) / 2;
	return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

float CTriangleShape::GetPerimeter() const
{
	float a = GetSide(m_point1, m_point2);
	float b = GetSide(m_point2, m_point3);
	float c = GetSide(m_point3, m_point1);

	return a + b + c;
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

float CTriangleShape::GetSide(const sf::Vector2f& point1, const sf::Vector2f& point2) const
{
	float dx = point2.x - point1.x;
	float dy = point2.y - point1.y;
	return std::sqrt(dx * dx + dy * dy);
}