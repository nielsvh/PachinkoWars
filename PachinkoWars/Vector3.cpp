#include "Vector3.h"

Vector3 Vector3::xAxis = Vector3(1,0,0);
Vector3 Vector3::yAxis = Vector3(0,1,0);
Vector3 Vector3::zAxis = Vector3(0,0,1);

Vector3::Vector3(void)
{
	x =y=z=0;
}

Vector3::Vector3(float _x, float _y, float _z):x(_x),y(_y),z(_z)
{
}


Vector3::~Vector3(void)
{
}

Vector3& Vector3::cross(const Vector3& other) const
{
	Vector3* result = new Vector3(y*other.z - z*other.y,
                      z*other.x - x*other.z,
                      x*other.y - y*other.x );
	return *result;
}

float Vector3::getLength(void)
{
	float ls = x*x + y*y + z*z;
	if (ls<.0001)
	{
		return 0;
	}
	return sqrt(ls);
}

Vector3* Vector3::normalize(void)
{
	float l = this->getLength();
	x/=l;y/=l;z/=l;
	return this;
}