#pragma once
#include "CShape.h"

class CRectangleShape final : public CBaseShape
{
public:
	CRectangleShape(const sf::Vector2f& point1, const sf::Vector2f& point2);

	float GetSquare() const override;
	float GetPerimeter() const override;
	void Draw(sf::RenderWindow& window) const override;
	std::string ToString() const override;
	sf::FloatRect GetBounds() const override; // Добавляем метод GetBounds


private:
	sf::Vector2f m_point1;
	sf::Vector2f m_point2;
};