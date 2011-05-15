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
	rtn.push_back(new Pin(p0));
	// (1-t)^3 * p0 + 3t(1-t)^2*p1 + 3t^2(1-t)p2+t^3*p3
	for (int i = 0; i< STEPS;i++)
	{
		p[i] = Point3(pow((1.0f-t),3.0f)*p0 + 3*t*pow((1.0f-t),2.0f)*p1 + 3*pow(t,2.0f)*(1.0-t)*p2 + pow(t,3.0f)*p3);

		Vector3 v = p[i]-rtn.back()->position;
		float l = v.getLength();
		if (l >= .2)
		{
			rtn.push_back(new Pin(p[i]));
		}

		t+=step;
	}
	return rtn;
}

vector<Pin*> PinLineCurve::GetLinePins( Point3 start, Point3 end )
{
	vector<Pin*> rtn;
	Vector3 v = end-start;
	int numSteps = v.getLength()/.55;
	v.normalize();
	v = .6f * v;
	Point3 c = start;
	rtn.push_back(new Pin(c));
	for (int i = 0;i<numSteps;i++)
	{
		rtn.push_back(new Pin(c+v));
		c = c+v;
	}

	/*Vector3 v2 = end-c;
	float rest = v2.getLength();

	if (rest!=0)
	{
		rtn.push_back(new Pin(c));
	}*/
	return rtn;
}
