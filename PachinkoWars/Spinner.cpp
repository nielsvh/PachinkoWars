#include "Spinner.h"
static Point3 points[24]= {
	Point3(1,0,0),Point3(0,0,0),Point3(0,1,0),
	Point3(0,1,0),Point3(0,0,0),Point3(-1,0,0),
	Point3(-1,0,0),Point3(0,0,0),Point3(0,-1,0),
	Point3(0,-1,0),Point3(0,0,0),Point3(1,0,0),

	Point3(1,0,1),Point3(0,0,1),Point3(0,1,1),
	Point3(0,1,1),Point3(0,0,1),Point3(-1,0,1),
	Point3(-1,0,1),Point3(0,0,1),Point3(0,-1,1),
	Point3(0,-1,1),Point3(0,0,1),Point3(1,0,1)
};

Spinner::Spinner(void)
{
}

Spinner::Spinner( Point3 newPos, float size )
{
	position = newPos;

}


Spinner::~Spinner(void)
{
}

void Spinner::Draw()
{

}
