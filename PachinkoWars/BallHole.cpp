#include "BallHole.h"


BallHole::BallHole(void)
{
}

BallHole::BallHole(Point3 pos, float h, float w)
{
	this->position = pos;
	this->width = w;
	this->height = h;
	objectType = HOLE;
	if (h>w)
		radius = h;
	else
		radius = w;

	points = new Point3[13];
	for (int i = 0;i<13;i++)
	{
		float theta = (2.0*PI/13.0)*i;
		points[i] = Point3(cos(theta)*width,sin(theta)*height, 0) + position;
	}
}

BallHole::~BallHole(void)
{
}

void BallHole::Draw()
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0;i<13;i++)
	{
		glVertex3f(points[i].x, points[i].y, points[i].z);
	}
	glEnd();
}
