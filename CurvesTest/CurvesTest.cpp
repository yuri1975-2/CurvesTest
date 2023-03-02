// CurvesTest.cpp: определяет точку входа для приложения.
//

#include "CurvesTest.h"

using namespace std;

const int NUMBER_OF_ELEMENTS = 10;
const double MAXIMUM_RADIUS = 100.0;
const pair<double, double> CURVE_CENTER = make_pair(0.0, 0.0);
const double MAXIMUM_Y_STEP = 10.0;
const double PI = acos(-1.0);

decltype(auto) getRandomRadius()
{
	return MAXIMUM_RADIUS * rand() / RAND_MAX;
}

decltype(auto) curveFactory()
{
	auto retValue(shared_ptr<ICurve>(nullptr));

	switch (rand() % 3)
	{
		case 0:
		{
			retValue = std::make_shared<Circle>(getRandomRadius(), CURVE_CENTER);
		}
		break;

		case 1:
		{
			retValue = std::make_shared<Ellipse>(getRandomRadius(), getRandomRadius(), CURVE_CENTER);
		}
		break;

		case 2:
		{
			retValue = std::make_shared<Helixe>(getRandomRadius(), getRandomRadius(), MAXIMUM_Y_STEP * rand() / RAND_MAX,
				CURVE_CENTER);
		}
		break;
	}

	return retValue;
}

void printCurve(const int number, const ICurve* const curve)
{
	cout << "line #" << number;
	
	if (nullptr == curve)
	{
		cout << "incorrect curve" << endl;
		return;
	}

	const vector<double> point(curve->getPoint(PI / 4));
	const vector<double> derivatives(curve->getFirstDerivatives(PI / 4));

	if ((3 != point.size()) || (3 != derivatives.size()))
	{
		cout << "incorrect curve" << endl;
		return;
	}

	cout << ", point = {" << point[0] << ", " << point[1] << ", " << point[2] << "}";
	cout << ", derivatives = {" << derivatives[0] << ", " << derivatives[1] << ", " << derivatives[2] << "}" << endl;
}

decltype(auto) isCircle(const ICurve* const curve)
{
	auto retValue(false);
	
	if (nullptr == curve)
	{
		return retValue;
	}

	if (curve->getZStep() > Helixe::EPSILON)
	{
		return retValue;
	}

	const auto radiuses(curve->getRadiuses());
	retValue = (abs(radiuses.first - radiuses.second) <= Helixe::EPSILON);

	return retValue;
}

void printCircle(const int lineNo, const ICurve* const circle)
{
	if (nullptr == circle)
	{
		return;
	}

	cout << "line#" << lineNo << ", radius: " << circle->getRadiuses().first << endl;
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	cout << fixed << showpoint;
	cout << setprecision(2);

	/*
	* populate container of randomly generated curves
	*/
	vector<shared_ptr<ICurve>> curves(NUMBER_OF_ELEMENTS);
	generate_n(curves.begin(), NUMBER_OF_ELEMENTS,
		[]()
		{
			return curveFactory();
		});
	
	/*
	* print point and derivatives for PI/4 for all previously generated curves
	*/
	auto lineNo(1);
	std::for_each(curves.cbegin(), curves.cend(),
		[&lineNo](const auto val)
		{
			printCurve(lineNo, val.get());
			++lineNo;
		});

	/*
	* get only circles from previously generated curves
	*/
	list<shared_ptr<ICurve>> circles;
	copy_if(curves.cbegin(), curves.cend(), back_inserter(circles),
		[](const auto val)
		{
			return isCircle(val.get());
		});
	cout << endl << "size of circles list: " << circles.size() << endl << endl;

	/*
	* circles2 is only to demonstate standalone sort() purposes (see following)
	*/
	vector<shared_ptr<ICurve>> circles2(circles.size());
	copy(circles.cbegin(), circles.cend(), circles2.begin());

	/*
	* sorting circles by radius by list::sort and STL standalone sort()
	*/
	const auto sortPredicate([](const auto val1, const auto val2)
	{
		const auto radiuses1(val1.get()->getRadiuses());
		const auto radiuses2(val2.get()->getRadiuses());
		return (radiuses1.first < radiuses2.first);
	});
	if (circles.size() > 1)
	{
		// list sort
		circles.sort(sortPredicate);
	}

	const auto printCircleFunction([&lineNo](const auto val)
		{
			printCircle(lineNo, val.get());
			++lineNo;
		});
	cout << endl << "results of list sort() member function:" << endl;
	lineNo = 1;
	std::for_each(circles.cbegin(), circles.cend(), printCircleFunction);



	/*
	* Example of using of standalone sort() STL algorithm
	*/
	if (circles2.size() > 1)
	{
		sort(circles2.begin(), circles2.end(), sortPredicate);
	}

	cout << endl << "results of standalone STL sort():" << endl;
	lineNo = 1;
	std::for_each(circles.cbegin(), circles.cend(), printCircleFunction);

	/*
	* total sum of radius for circles
	*/
	if (circles.size() > 0)
	{
		auto radiusSum(0.0);
		radiusSum = accumulate(circles.cbegin(), circles.cend(), radiusSum,
			[](const auto accValue, const auto currentValue)
			{
				return (accValue + currentValue.get()->getRadiuses().first);
			});
		cout << endl << "radius sum: " << radiusSum << endl;
	}

	return 0;
}
