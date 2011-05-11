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
	Vector3 v1 = points[1]-points[0], v2 = points[2] - points[0];
	normal = v1.cross(v2);
	normal.normalize();
}


Plane::~Plane(void)
{
}

Point3 Plane::ClosestPointToPoint( Point3 p )
{
	Vector3 v = p - points[0];
	Vector3 proj = (v*normal)*normal;
	return p - proj;
}
