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
};

