#ifndef SHAPE_H
#define SHAPE_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>

#define _USE_MATH_DEFINES
#include <math.h>

class CBaseShape
{
public:
	virtual ~CBaseShape() = default;
	virtual float GetSquare() const = 0;
	virtual float GetPerimeter() const = 0;
	virtual void Draw(sf::RenderWindow& window) const = 0;
	virtual std::string ToString() const = 0;
	
};

#endif 
