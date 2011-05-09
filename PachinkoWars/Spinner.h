#pragma once
#include <gl/glut.h>
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
	Point3 boundingCube[8];
	void Draw();
	void Update();
	void Init();

	float mass;
	Quaternion temp,temp1,temp2;
	Quaternion rotation;
	Vector3 angularVel, angularAcc;

	Vector3 totalForce;
	Matrix33* tensor;
	Vector3 myL;
	Vector3 lastTorque;
};

