#include "Helixe.h"
#include <stdexcept>

const double Helixe::PI_X_2 = 2 * acos(-1.0);
const double Helixe::EPSILON = 0.0001;
const char* const Helixe::INVALID_RADIUS_MESSAGE = "Invalid Radius"; 

Helixe::Helixe(const double radius, const double radius2, const double ZStep,
	const pair<double, double> center)
{
	if (radius <= EPSILON)
	{
		throw invalid_argument(INVALID_RADIUS_MESSAGE);
	}

	mRadius = radius;

	if (radius2 <= EPSILON)
	{
		throw invalid_argument(INVALID_RADIUS_MESSAGE);
	}
	mRadius2 = radius2;

	if (ZStep < 0.0)
	{
		throw invalid_argument(INVALID_RADIUS_MESSAGE);
	}
	mZStep = ZStep;

	mCenter = center;
}