#include "CCircle.h"

CCircleShape::CCircleShape(const sf::Vector2f& center, float radius)
	: m_center(center), m_radius(radius) {}

float CCircleShape::GetSquare() const
{
	return M_PI * m_radius * m_radius;
}

float CCircleShape::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

void CCircleShape::Draw(sf::RenderWindow& window) const
{
	sf::CircleShape circle(m_radius);
	circle.setPosition(m_center);
	circle.setFillColor(sf::Color::Green);
	window.draw(circle);
}


std::string CCircleShape::ToString() const
{
	std::stringstream ss;
	ss << "CIRCLE: P=" << GetPerimeter() << "; S=" << GetSquare();
	return ss.str();
}