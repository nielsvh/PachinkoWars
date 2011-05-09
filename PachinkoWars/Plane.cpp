#include "Plane.h"


Plane::Plane(void)
{
}

// p0 is center, p1 and p2 radiate from it.
Plane::Plane( Point3 p0, Point3 p1, Point3 p2 )
{
	points[0] = p0;
	points[1] = p1;
	points[2] = p2;
}


Plane::~Plane(void)
{
}

Vector3 Plane::GetNormal()
{
	Vector3 v1 = points[1]-points[0], v2 = points[2] - points[0];
	return v1.cross(v2);
}
