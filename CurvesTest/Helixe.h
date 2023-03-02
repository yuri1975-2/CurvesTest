#pragma once
#include "ICurve.h"

class Helixe : public ICurve
{
private:
	double mRadius;
	pair<double, double> mCenter;
	double mRadius2;
	double mZStep;

	static const char* const INVALID_RADIUS_MESSAGE;
	static const double PI_X_2;

public:
	static const double EPSILON;

	Helixe() = delete;

	Helixe(const double radius, const double radius2, const double ZStep, const pair<double, double> center);

	virtual vector<double> getPoint(const double angle) const override
	{
		const auto ZCoord((mZStep <= EPSILON) ? 0 : angle / PI_X_2 * mZStep);
		return { mRadius * cos(angle) + mCenter.first, mRadius2 * sin(angle) + mCenter.second, ZCoord };
	}

	virtual vector<double> getFirstDerivatives(const double angle) const override
	{
		const auto ZCoord((mZStep <= EPSILON) ? 0.0 : 1.0);
		return { -mRadius * sin(angle), mRadius2 * cos(angle), ZCoord };
	}

	virtual pair<double, double> getRadiuses() const override
	{
		return make_pair(mRadius, mRadius2);
	}

	virtual double getZStep() const override
	{
		return mZStep;
	}

	~Helixe()
	{
	}
};