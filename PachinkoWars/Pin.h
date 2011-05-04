#pragma once
#include <gl/glut.h>
#include "Matrix33.h"
#include "GameObject.h"

class Pin : public GameObject
{
public:
	Pin(void);
	Pin(Point3 myPosition);
	~Pin(void);
	Point3 points[22];
	void Draw();
};

