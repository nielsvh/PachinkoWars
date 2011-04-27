#pragma once
#include "Vector3.h"
class Quaternion
{
public:
	Quaternion(void);
	Quaternion(float w, float x, float y, float z);
	Quaternion(float alpha, float beta, float gamma);
	Quaternion(Vector3& axis, float angle);
	Quaternion(Vector3& vector);
	~Quaternion(void);

	double getLength(void);
	void normalize(void);
	Quaternion* inverse();

	float x,y,z,w;
	static void getAxisAngle(Quaternion &q, Vector3 &v, float &angle)
	{
		float tempAngle = acos(q.w);
		float scale = q.getLength();

		if(scale == 0.0f)
		{
			angle = 0.0f;
			v = Vector3(1.0f,0.0f,0.0f);
		}
		else
		{
			angle = tempAngle*2.0f;
			v=Vector3(q.x/scale, q.y/scale, q.z/scale);
		}
	}

	Vector3* rotate(const Vector3 vector)const;

	void operator=(const Vector3& rhs)
	{
		x=rhs.x;
		y=rhs.y;
		z=rhs.z;
		w = 0.0f;
	}

	Quaternion& operator*(Quaternion& rhs)
	{
		/*a1a2-b1b2-c1c2-d1d2,
		a1b2+b1a2+c1d2-d1c2,
		a1c2-b1d2+c1a2+d1b2,
		a1d2+b1c2-c1b2+d1a2;*/
		Quaternion* tmp = new Quaternion(*this);
		tmp->w = this->w*rhs.w - this->x*rhs.x - this->y*rhs.y - this->z*rhs.z;
		tmp->x = this->w*rhs.x + this->x*rhs.w + this->y*rhs.z - this->z*rhs.y;
		tmp->y = this->w*rhs.y - this->x*rhs.z + this->y*rhs.w + this->z*rhs.x;
		tmp->z = this->w*rhs.z + this->x*rhs.y - this->y*rhs.x + this->z*rhs.w;
		return *tmp;
	}

	Quaternion& operator+(Quaternion& rhs)
	{
		Quaternion q = *this;
		q.w += rhs.w;
		q.x += rhs.x;
		q.y += rhs.y;
		q.z += rhs.z;
		return q;
	}
};

static Quaternion& operator*(float lhs, Quaternion& q)
{
	q.w*=lhs;q.x*=lhs;q.y*=lhs;q.z*=lhs;
	return q;
}