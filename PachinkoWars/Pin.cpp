#include "Pin.h"


Pin::Pin(void)
{
}

Pin::Pin( Point3 myPosition )
{
	position = myPosition;
	Point3 apoints[22] = {
		Point3(0,0,0),Point3(0,1,0),
		Point3(1/16.f, 0,0),Point3(1/16.f, 1.-3/16.f,0),Point3(1/8.f, 1.-1/8.f, 0),Point3(5/16.f, 1.0-1/8., 0),Point3(5/16.f, 1, 0),
		Point3(-1/16.f, 0,0),Point3(-1/16.f, 1.-3/16.f,0),Point3(-1/8.f, 1.-1/8.f, 0),Point3(-5/16.f, 1.0-1/8., 0),Point3(-5/16.f, 1, 0),
		Point3(0, 0,1/16.f),Point3(0, 1.-3/16.f,1/16.f),Point3(0, 1.-1/8.f, 1/8.f),Point3(0, 1.0-1/8., 5/16.f),Point3(0, 1, 5/16.f),
		Point3(0, 0,-1/16.f),Point3(0, 1.-3/16.f,-1/16.f),Point3(0, 1.-1/8.f, -1/8.f),Point3(0, 1.0-1/8., -5/16.f),Point3(0, 1, -5/16.f)
	};
	for (int i = 0;i<22;i++)
	{
		points[i] =  apoints[i]+myPosition;
	}
}


Pin::~Pin(void)
{
}

void Pin::Draw()
{
	/*glBegin(GL_LINE_LOOP);
	glVertex3f(points[0].x, points[0].y, points[0].z);
	glVertex3f(points[2].x, points[2].y, points[2].z);
	glVertex3f(points[3].x, points[3].y, points[3].z);
	glVertex3f(points[4].x, points[4].y, points[4].z);
	glVertex3f(points[5].x, points[5].y, points[5].z);
	glVertex3f(points[6].x, points[6].y, points[6].z);
	glVertex3f(points[1].x, points[1].y, points[1].z);
	glVertex3f(points[11].x, points[11].y, points[11].z);
	glVertex3f(points[10].x, points[10].y, points[10].z);
	glVertex3f(points[9].x, points[9].y, points[9].z);
	glVertex3f(points[8].x, points[8].y, points[8].z);
	glVertex3f(points[7].x, points[7].y, points[7].z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(points[0].x, points[0].y, points[0].z);
	glVertex3f(points[12].x, points[12].y, points[12].z);
	glVertex3f(points[13].x, points[13].y, points[13].z);
	glVertex3f(points[14].x, points[14].y, points[14].z);
	glVertex3f(points[15].x, points[15].y, points[15].z);
	glVertex3f(points[16].x, points[16].y, points[16].z);
	glVertex3f(points[1].x, points[1].y, points[1].z);
	glVertex3f(points[21].x, points[21].y, points[21].z);
	glVertex3f(points[20].x, points[20].y, points[20].z);
	glVertex3f(points[19].x, points[19].y, points[19].z);
	glVertex3f(points[18].x, points[18].y, points[18].z);
	glVertex3f(points[17].x, points[17].y, points[17].z);
	glEnd();*/

	glBegin(GL_POINTS);
	glVertex3f(position.x, position.y, position.z);
	glEnd();
}
