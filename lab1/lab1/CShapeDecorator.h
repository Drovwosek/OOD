#ifndef SHAPE_DECORATOR_H
#define SHAPE_DECORATOR_H

#include "CShape.h"

class CShapeDecorator : public CBaseShape
{
public:
    CShapeDecorator(std::shared_ptr<CBaseShape> shape, sf::Color borderColor)
        : m_shape(shape), m_borderColor(borderColor) {}

    float GetSquare() const override
    {
        return m_shape->GetSquare();
    }

    float GetPerimeter() const override
    {
        return m_shape->GetPerimeter();
    }

    void Draw(sf::RenderWindow& window) const override
    {
        m_shape->Draw(window);

        // Добавляем обводку
        sf::FloatRect bounds = m_shape->GetBounds();
        sf::RectangleShape border(sf::Vector2f(bounds.width, bounds.height));
        border.setPosition(bounds.left, bounds.top);
        border.setOutlineColor(m_borderColor);
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineThickness(2); // Толщина обводки
        window.draw(border);
    }

    std::string ToString() const override
    {
        return m_shape->ToString();
    }

    sf::FloatRect GetBounds() const override
    {
        return m_shape->GetBounds();
    }

private:
    std::shared_ptr<CBaseShape> m_shape;
    sf::Color m_borderColor;
};

#endif
