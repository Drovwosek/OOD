#include "CRectangle.h"

CRectangleShape::CRectangleShape(const sf::Vector2f& point1, const sf::Vector2f& point2)
	: m_point1(point1), m_point2(point2) {}

float CRectangleShape::GetSquare() const
{
	return std::abs(m_point2.x - m_point1.x) * std::abs(m_point2.y - m_point1.y);
}

float CRectangleShape::GetPerimeter() const
{
	return 2 * (std::abs(m_point2.x - m_point1.x) + std::abs(m_point2.y - m_point1.y));
}

void CRectangleShape::Draw(sf::RenderWindow& window) const
{
	sf::RectangleShape rectangle;
	rectangle.setPosition(m_point1);
	rectangle.setSize(sf::Vector2f(std::abs(m_point2.x - m_point1.x), std::abs(m_point2.y - m_point1.y)));
	rectangle.setFillColor(sf::Color::Red);
	window.draw(rectangle);
}

std::string CRectangleShape::ToString() const
{
	std::stringstream ss;
	ss << "RECTANGLE: P=" << GetPerimeter() << "; S=" << GetSquare();
	return ss.str();
}
