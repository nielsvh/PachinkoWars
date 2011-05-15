#include "Spinner.h"
Point3 Spinner::staticPoints[24]= {
	Point3(1,.2,1),Point3(.2,.2,1),Point3(.2,1,1),
	Point3(-.2,1,1),Point3(-.2,.2,1),Point3(-1,.2,1),
	Point3(-1,-.2,1),Point3(-.2,-.2,1),Point3(-.2,-1,1),
	Point3(.2,-1,1),Point3(.2,-.2,1),Point3(1,-.2,1),

	Point3(1,.2,0),Point3(.2,.2,0),Point3(.2,1,0),
	Point3(-.2,1,0),Point3(-.2,.2,0),Point3(-1,.2,0),
	Point3(-1,-.2,0),Point3(-.2,-.2,0),Point3(-.2,-1,0),
	Point3(.2,-1,0),Point3(.2,-.2,0),Point3(1,-.2,0)
};

Spinner::Spinner(void)
{
}

Spinner::Spinner( Point3 newPos, float size, float m )
{
	planes = new Plane[12];
	position = newPos;
	mass = m;
	radius = size;
	objectType = SPINNER;
	Init();
}

void Spinner::Init()
{
	angularAcc = Vector3();
	angularVel = Vector3(0,0,0);
	rotation = Quaternion(1,0,0,0);
	tensor = new Matrix33();

	tensor->myMatrix[0] = (1.f/12.f)*mass*(3*radius*radius + (points[0].z-points[12].z)*(points[0].z-points[12].z));
	tensor->myMatrix[4] = (1.f/12.f)*mass*(3*radius*radius + (points[0].z-points[12].z)*(points[0].z-points[12].z));
	tensor->myMatrix[8] = mass*radius*radius;
	myL = *tensor * angularVel;

	boundingCube[0] = Point3(-1,-1,0);
	boundingCube[1] = Point3(1,-1,0);
	boundingCube[2] = Point3(1,1,0);
	boundingCube[3] = Point3(-1,1,0);

	boundingCube[4] = Point3(-1,-1,1);
	boundingCube[5] = Point3(1,-1,1);
	boundingCube[6] = Point3(1,1,1);
	boundingCube[7] = Point3(-1,1,1);

	for (int i = 0;i<24;i++)
	{
		points[i] = radius * staticPoints[i];
		points[i] = points[i] + position;
	}

	for (int i = 0;i<8;i++)
	{
		boundingCube[i] = radius * boundingCube[i];
		boundingCube[i] = boundingCube[i]+position;
	}

	planes[0] = Plane(points[5], points[17], points[6]);
	planes[1] = Plane(points[6], points[18], points[7]);
	planes[2] = Plane(points[7], points[19], points[8]);

	planes[3] =  Plane(points[8], points[20], points[9]);
	planes[4] =  Plane(points[9], points[21], points[10]);
	planes[5] =  Plane(points[10], points[22], points[11]);

	planes[6] =  Plane(points[11], points[23], points[0]);
	planes[7] =  Plane(points[0], points[12], points[1]);
	planes[8] =  Plane(points[1], points[13], points[2]);

	planes[9] =  Plane(points[2], points[14], points[3]);
	planes[10] =  Plane(points[3], points[15], points[4]);
	planes[11] =  Plane(points[4], points[16], points[5]);
}

void Spinner::Update()
{
	for (int i = 0;i<24;i++)
	{
		Vector3 v = points[i]-position;
		Quaternion qv = Quaternion(v);
		Quaternion invRot = rotation.Inverse();
		Quaternion rot = rotation * qv;
		rot = rot * invRot;
		Point3 p = (Point3)(radius * staticPoints[i]);
		points[i] = position + Point3(rot.x, rot.y, rot.z);
	}
	for (int i = 0;i<8;i++)
	{
		boundingCube[i] = radius * boundingCube[i];
		boundingCube[i] = boundingCube[i]+position;
	}

	planes[0] = Plane(points[5], points[17], points[6]);
	planes[1] = Plane(points[6], points[18], points[7]);
	planes[2] = Plane(points[7], points[19], points[8]);

	planes[3] =  Plane(points[8], points[20], points[9]);
	planes[4] =  Plane(points[9], points[21], points[10]);
	planes[5] =  Plane(points[10], points[22], points[11]);

	planes[6] =  Plane(points[11], points[23], points[0]);
	planes[7] =  Plane(points[0], points[12], points[1]);
	planes[8] =  Plane(points[1], points[13], points[2]);

	planes[9] =  Plane(points[2], points[14], points[3]);
	planes[10] =  Plane(points[3], points[15], points[4]);
	planes[11] =  Plane(points[4], points[16], points[5]);
}

Spinner::~Spinner(void)
{
}

void Spinner::Draw()
{
	// 0 1 10 11
	glBegin(GL_LINE_LOOP);
	glVertex3f(points[0].x,points[0].y,points[0].z);
	glVertex3f(points[1].x,points[1].y,points[1].z);
	glVertex3f(points[10].x,points[10].y,points[10].z);
	glVertex3f(points[11].x,points[11].y,points[11].z);
	glEnd();
	// 1 2 3 4
	glBegin(GL_LINE_LOOP);
	glVertex3f(points[1].x,points[1].y,points[1].z);
	glVertex3f(points[2].x,points[2].y,points[2].z);
	glVertex3f(points[3].x,points[3].y,points[3].z);
	glVertex3f(points[4].x,points[4].y,points[4].z);
	glEnd();
	// 4 5 6 7
	glBegin(GL_LINE_LOOP);
	glVertex3f(points[4].x,points[4].y,points[4].z);
	glVertex3f(points[5].x,points[5].y,points[5].z);
	glVertex3f(points[6].x,points[6].y,points[6].z);
	glVertex3f(points[7].x,points[7].y,points[7].z);
	glEnd();
	// 4 8 9 1
	glBegin(GL_LINE_LOOP);
	glVertex3f(points[4].x,points[4].y,points[4].z);
	glVertex3f(points[8].x,points[8].y,points[8].z);
	glVertex3f(points[9].x,points[9].y,points[9].z);
	glVertex3f(points[1].x,points[1].y,points[1].z);
	glEnd();

	// 0 1 13 12
	for (int i = 0;i<12;i++)
	{
		if (i+13 <= 23)
		{
			glBegin(GL_LINE_LOOP);
			glVertex3f(points[i].x,points[i].y,points[i].z);
			glVertex3f(points[i+1].x,points[i+1].y,points[i+1].z);
			glVertex3f(points[i+1+12].x,points[i+1+12].y,points[i+1+12].z);
			glVertex3f(points[i+12].x,points[i+12].y,points[i+12].z);
			glEnd();
		}
		else{
			glBegin(GL_LINE_LOOP);
			glVertex3f(points[i].x,points[i].y,points[i].z);
			glVertex3f(points[0].x,points[0].y,points[0].z);
			glVertex3f(points[12].x,points[12].y,points[12].z);
			glVertex3f(points[i+12].x,points[i+12].y,points[i+12].z);
			glEnd();
		}
	}
}
