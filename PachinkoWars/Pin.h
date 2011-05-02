#pragma once
#include <gl/glut.h>
#include "Matrix33.h"

class Pin
{
public:
	Pin(void);
	Pin(Point3 myPosition);
	~Pin(void);
	Point3 position;
	Point3 points[22];
	void Draw();
};

