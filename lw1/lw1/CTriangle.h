#pragma once
#include "CShape.h"

class CTriangleShape final : public CBaseShape
{
public:
	CTriangleShape(const sf::Vector2f& point1, const sf::Vector2f& point2, const sf::Vector2f& point3);

	float GetSquare() const override;
	float GetPerimeter() const override;
	void Draw(sf::RenderWindow& window) const override;
	std::string ToString() const override;
	
private:
	sf::Vector2f m_point1;
	sf::Vector2f m_point2;
	sf::Vector2f m_point3;
	float GetSide(const sf::Vector2f& point1, const sf::Vector2f& point2) const;
};