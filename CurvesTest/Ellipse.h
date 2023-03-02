#pragma once
#include "Helixe.h"

class Ellipse : public Helixe
{
public:
	Ellipse() = delete;

	Ellipse(const double radius, const double radius2, const pair<double, double> center) 
		: Helixe(radius, radius2, Helixe::EPSILON / 2, center)
	{
	}

	~Ellipse()
	{
	}
};