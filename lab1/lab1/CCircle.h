#ifndef CIRCLE_H
#define CIRCLE_H
#pragma once
#include "CShape.h"

class CCircleShape final : public CBaseShape
{
public:
	CCircleShape(const sf::Vector2f& center, float radius);

	float GetSquare() const override;
	float GetPerimeter() const override;
	void Draw(sf::RenderWindow& window) const override;
	std::string ToString() const override;
	sf::FloatRect GetBounds() const override; // Добавляем метод GetBounds

private:
	sf::Vector2f m_center;
	float m_radius;
};
#endif 
