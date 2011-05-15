#include "Quaternion.h"


Quaternion::Quaternion(void)
{
	x=0.0f,y=0.0f,z=0.0f,w=0.0f;
}

Quaternion::Quaternion(float _w, float _x, float _y, float _z):
w(_w),x(_x),y(_y),z(_z)
{
}

Quaternion::Quaternion(float alpha, float beta, float gamma)
{
	// alpha is z, beta is x, gamma is y
//	double ca = cos(alpha/2.0f), cb = cos(beta/2.0f), cg = cos(gamma/2.0f), sa = sin(alpha/2.0f), sb = sin(beta/2.0f), sg = sin(gamma/2.0f);
//	w = ca*cb*cg+sa*sb*sg;
//	x = sa*cb*cg-ca*sb*sg;
//	y = ca*sb*cg+sa*cb*sg;
//	z = ca*cb*sg-sa*sb*cg;
	
	double c1 = cos(alpha);
	double s1 = sin(alpha);
	double c2 = cos(beta);
	double s2 = sin(beta);
	double c3 = cos(gamma);
	double s3 = sin(gamma);
	w = sqrt(1.0 + c1 * c2 + c1*c3 - s1 * s2 * s3 + c2*c3) / 2.0;
	double w4 = (4.0 * w);
	x = (c2 * s3 + c1 * s3 + s1 * s2 * c3) / w4 ;
	y = (s1 * c2 + s1 * c3 + c1 * s2 * s3) / w4 ;
	z = (-s1 * s3 + c1 * s2 * c3 +s2) / w4 ;
}

// angle in DEGREES
Quaternion::Quaternion( Vector3& axis, float angle )
{
	float rad = angle * PI / 180;
	this->w = cos(rad/2);
	this->x = axis.x * sin(rad/2);
	this->y = axis.y * sin(rad/2);
	this->z = axis.z * sin(rad/2);
}

Quaternion::Quaternion( Vector3& vector )
{
	this->w = 0;
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
}

Quaternion::~Quaternion(void)
{
}

double Quaternion::getLength(void)
{
	return sqrt(w*w+x*x+y*y+z*z);
}

void Quaternion::normalize(void)
{
	double l = this->getLength();
	this->w/=l;this->x/=l;this->y/=l;this->z/=l;
}

const Vector3 Quaternion::rotate(const Vector3& vector)const
{
	float vMult = 2.0f*(x*vector.x+y*vector.y+z*vector.z);
	float crossMult = 2.0f*w;
	float pMult = crossMult*w - 1.0f;

	return Vector3(	pMult*vector.x+vMult*x + crossMult*(y*vector.z-z*vector.y),
					pMult*vector.y+vMult*y + crossMult*(z*vector.x-x*vector.z),
					pMult*vector.z+vMult*z + crossMult*(x*vector.y-y*vector.x));
}

Quaternion Quaternion::Inverse()
{
	Quaternion tmp = Quaternion(this->w, -this->x, -this->y, -this->z);
	return tmp;
}
