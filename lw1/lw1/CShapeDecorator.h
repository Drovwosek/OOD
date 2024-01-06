#include "CShape.h"

class CShapeDecorator : public CBaseShape
{
public:
    CShapeDecorator(std::shared_ptr<CBaseShape> shape)
        : m_shape(shape) {}

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

       
    }

    std::string ToString() const override
    {
        return m_shape->ToString();
    }

    

private:
    std::shared_ptr<CBaseShape> m_shape;
    sf::Color m_borderColor;
};
