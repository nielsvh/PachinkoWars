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

 static const Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	Vector3* newVec = new Vector3(lhs.x+rhs.x,lhs.y+rhs.y,lhs.z+rhs.z);
	return *newVec;
};
static const float operator*(const Vector3& lhs, const Vector3& rhs)
{
	float total;
	total = lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	return total;
};
static const Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	float x = lhs.x - rhs.x,y = lhs.y - rhs.y,z = lhs.z - rhs.z;
	Vector3 newVec = Vector3(x,y,z);
	return newVec;
};
static const Vector3 operator*(const float& lhs, const Vector3& rhs)
{
	Vector3 newVec = Vector3(lhs * rhs.x,lhs * rhs.y,lhs * rhs.z);
	return newVec;
};

static const Vector3 calculateUp(Vector3& lookAt, Vector3& eye, Vector3& up){
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

static const Vector3 operator-(const Point3& lhs, const Point3& rhs)
{
	return Vector3(lhs.x-rhs.x,lhs.y-rhs.y,lhs.z-rhs.z);
};

static const Point3 operator+(const Point3& p, const Vector3& v)
{
	float x = p.x+v.x,y = p.y+v.y,z =  p.z+v.z;
	Point3 result = Point3(x, y, z);
	return result;
};

static const Point3 operator-(const Point3& p, const Vector3& v)
{
	Point3* result = new Point3(p.x-v.x, p.y-v.y, p.z-v.z);
	return *result;
};

static const Point3 operator*(const float& f, const Point3& p)
{
	Point3* rtn = new Point3(p.x*f, p.y*f,p.z*f);
	return *rtn;
}

static const Vector3 project( const Vector3& a, const Vector3& b )
{
	Vector3 bhat = b;
	bhat.normalize();
	Vector3 c = Vector3(((Vector3&)a).getLength() * 1.0f/(((Vector3&)a).getLength()*((Vector3&)b).getLength()) * (a*b) * bhat);
	return c;
}

static const Vector3 rejection(const Vector3& a, const Vector3& b)
{
	Vector3 bhat = b;
	bhat.normalize();
	float adotb = (a*bhat);
	Vector3 scaleB = adotb * bhat;
	Vector3 aminb = a - scaleB;
	return aminb;
}