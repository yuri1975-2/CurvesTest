#pragma once

#include <vector>

using namespace std;

class ICurve
{
public:
	
	virtual vector<double> getPoint(const double angle) const = 0;
	virtual vector<double> getFirstDerivatives(const double angle) const = 0;
	virtual pair<double, double> getRadiuses() const = 0;
	virtual double getZStep() const = 0;

	virtual ~ICurve() {};
};