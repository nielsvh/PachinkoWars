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

	Point3& operator*(double rhs)
	{
		x*=rhs;
		y*=rhs;
		z*=rhs;
		return *this;
	}

	Point3& operator+(Point3& rhs)
	{
		x += rhs.x;
		y+=rhs.y;
		z+=rhs.z;
		return *this;
	}
};

