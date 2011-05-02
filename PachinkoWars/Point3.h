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
		Point3* tmp = new Point3(*this);
		tmp->x*=rhs;
		tmp->y*=rhs;
		tmp->z*=rhs;
		return *tmp;
	}

	Point3& operator+(Point3& rhs)
	{
		Point3* tmp = new Point3(*this);
		tmp->x += rhs.x;
		tmp->y+=rhs.y;
		tmp->z+=rhs.z;
		return *tmp;
	}
};

