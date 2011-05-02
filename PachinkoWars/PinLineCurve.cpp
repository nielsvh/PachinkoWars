#include "PinLineCurve.h"
#define STEPS 100

PinLineCurve::PinLineCurve(void)
{
}


PinLineCurve::~PinLineCurve(void)
{
}

vector<Pin*> PinLineCurve::GetCurvePins( Point3 p0, Point3 p1, Point3 p2, Point3 p3 )
{
	vector<Pin*> rtn;
	float t = 0, step = 1.0/STEPS;
	Point3 p[STEPS];
	// (1-t)^3 * p0 + 3t(1-t)^2*p1 + 3t^2(1-t)p2+t^3*p3
	for (int i = 0; i< STEPS;i++)
	{
		p[i] = Point3(p0*pow((1.0f-t),3.0f) + p1*3*t*pow((1.0f-t),2.0f) + p2*3*pow(t,2.0f)*(1.0-t) + p3*pow(t,3.0f));
		t+=step;
	}
	return rtn;
}

vector<Pin*> PinLineCurve::GetLinePins( Point3 start, Point3 end )
{
	vector<Pin*> rtn;
	return rtn;
}
