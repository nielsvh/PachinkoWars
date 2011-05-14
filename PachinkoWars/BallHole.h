#pragma once
#include "GameObject.h"
#include <gl/glut.h>

class BallHole :
	public GameObject
{
public:
	BallHole(void);
	BallHole(Point3 position, float h, float w);
	~BallHole(void);
	Point3* points;
	void Draw();
	float width, height;
};

