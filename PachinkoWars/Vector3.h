#pragma once
#include "Point3.h"
#include <math.h>

class Vector3
{
public:
	Vector3(void);
	Vector3(float x, float y, float z);
	~Vector3(void);
	float x,y,z;

	Vector3& cross(const Vector3& other) const;
	float getLength(void);
	Vector3* normalize(void);
	
	static Vector3 xAxis;
	static Vector3 yAxis;
	static Vector3 zAxis;
};

 static Vector3& operator+(Vector3& lhs, Vector3& rhs)
{
	Vector3* newVec = new Vector3(lhs.x+rhs.x,lhs.y+rhs.y,lhs.z+rhs.z);
	return *newVec;
};
static float& operator*(Vector3& lhs, Vector3& rhs)
{
	float* total = new float;
	*total = lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	return *total;
};
static Vector3& operator-(Vector3& lhs, Vector3& rhs)
{
	Vector3* newVec = new Vector3(lhs.x - rhs.x,lhs.y - rhs.y,lhs.z - rhs.z);
	return *newVec;
};
static Vector3& operator*(float lhs, Vector3& rhs)
{
	Vector3* newVec = new Vector3(lhs * rhs.x,lhs * rhs.y,lhs * rhs.z);
	return *newVec;
};

static Vector3& calculateUp(Vector3& lookAt, Vector3& eye, Vector3& up){
	//Vector3* viewUp = new Vector3();
	float length;

	// calculate view direction
	Vector3* viewDir = new Vector3(lookAt.x - eye.x,lookAt.y - eye.y,lookAt.z - eye.z);

	// find length of vector
	length = sqrt((*viewDir).x*(*viewDir).x + (*viewDir).y * (*viewDir).y + (*viewDir).z*(*viewDir).z);
	// normalize
	viewDir->x /= length;
	viewDir->y /= length;
	viewDir->z /= length;

	// calculate up
	//viewUp = up - up.dot(viewDir)*viewDir
	return up-((up* (*viewDir))*(*viewDir));
};

static Vector3& operator-(Point3& lhs, Point3& rhs)
{
	return Vector3(lhs.x-rhs.x,lhs.y-rhs.y,lhs.z-rhs.z);
};

static Point3& operator+(Point3& p, Vector3& v)
{
	Point3 *result = new  Point3(p.x+v.x, p.y+v.y, p.z+v.z);
	return *result;
};

static Point3& operator-(Point3& p, Vector3& v)
{
	Point3* result = new Point3(p.x-v.x, p.y-v.y, p.z-v.z);
	return *result;
};

static Point3& operator*(float f, Point3& p)
{
	Point3* rtn = new Point3(p.x*f, p.y*f,p.z*f);
	return *rtn;
}