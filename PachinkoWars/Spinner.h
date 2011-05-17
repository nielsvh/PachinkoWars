#pragma once
#include <gl/glut.h>
#include "GameObject.h"
#include "Matrix33.h"
#include "Plane.h"

class Spinner:public GameObject
{
public:
	Spinner(void);
	Spinner(Point3 newPos, float size, float mass);
	~Spinner(void);
	static Point3 staticPoints[24];
	static Point3 staticBoundingCube[8];
	Point3 points[24];
	Point3 boundingCube[8];
	void Draw();
	void Update();
	void Init();
	Quaternion Rotation() const { return rotation; }
	void Rotation(Quaternion val) { rotation = val; }
	Vector3 MyL() const { return myL; }
	void MyL(Vector3 val) { myL = val; }
	Vector3 AngularVel() const { return angularVel; }
	void AngularVel(Vector3 val) { angularVel = val; }
	Matrix33* Tensor() const { return tensor; }
	void Tensor(Matrix33* val) { tensor = val; }
	Plane* Planes() const { return planes; }
	void Planes(Plane* val) { planes = val; }

private:
	float mass;
	Quaternion temp,temp1,temp2;
	Quaternion rotation;
	Vector3 angularVel, angularAcc;
	Vector3 totalForce;
	Matrix33* tensor;
	Vector3 myL;
	Vector3 lastTorque;
	Plane* planes;
};

