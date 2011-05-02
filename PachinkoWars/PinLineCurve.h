#pragma once
#include <vector>
#include <math.h>
#include "Pin.h"
#include "Vector3.h"
using namespace std;
class PinLineCurve
{
public:
	PinLineCurve(void);
	~PinLineCurve(void);
	static vector<Pin*> GetCurvePins(Point3 p0, Point3 p1, Point3 p2, Point3 p3);
	static vector<Pin*> GetLinePins(Point3 start, Point3 end);
};

