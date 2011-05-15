#pragma once
#include "Vector3.h"
class Plane
{
public:
	Plane(void);
	Plane(Point3 p0, Point3 p1, Point3 p2);
	Point3 points[3];
	~Plane(void);
	Vector3 normal;
	Point3 ClosestPointToPoint(Point3 p);
	bool Behind( Point3 point );
};

