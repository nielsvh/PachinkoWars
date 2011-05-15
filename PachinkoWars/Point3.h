#pragma once
#include <stdlib.h>
#include <gl/glut.h>
#include <math.h>
#include "Maths.h"

class Point3
{
public:
	Point3(void);
	Point3(float newX, float newY, float newZ);
	~Point3(void);
	float x,y,z;

	const Point3 operator*(const double rhs)
	{
		Point3 tmp;
		tmp.x= rhs * this->x;
		tmp.y=rhs * this->y;
		tmp.z=rhs * this->z;
		return tmp;
	}

	const Point3 operator+(const Point3& rhs) const
	{
		Point3 tmp;
		tmp.x = rhs.x + this->x;
		tmp.y=rhs.y + this->y;
		tmp.z=rhs.z + this->z;
		return tmp;
	}
};

