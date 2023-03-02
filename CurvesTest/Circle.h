#pragma once

#include "Ellipse.h"

class Circle : public Ellipse
{
public:
	Circle() = delete;

	Circle(const double radius, const pair<double, double> center) : Ellipse(radius, radius, center)
	{
	}
	
	~Circle()
	{
	}
};