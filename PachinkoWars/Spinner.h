#pragma once
#include "GameObject.h"
#include "Matrix33.h"

class Spinner:public GameObject
{
public:
	Spinner(void);
	Spinner(Point3 newPos, float size);
	~Spinner(void);
	static Point3 staticPoints[24];
	Point3 points[24];
	void Draw();
};

