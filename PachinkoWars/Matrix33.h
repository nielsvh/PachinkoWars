#pragma once
#include "Quaternion.h"

class Matrix33
{
public:
	Matrix33(void);
	Matrix33(const Quaternion& q);
	~Matrix33(void);
	float* myMatrix;
	
	Matrix33 operator*(Matrix33& rhs) const
	{
		Matrix33 result;
		result.myMatrix[0] = rhs.myMatrix[0]*myMatrix[0]+rhs.myMatrix[1]*myMatrix[3]+rhs.myMatrix[2]*myMatrix[6];
		result.myMatrix[1] = rhs.myMatrix[0]*myMatrix[1]+rhs.myMatrix[1]*myMatrix[4]+rhs.myMatrix[2]*myMatrix[7];
		result.myMatrix[2] = rhs.myMatrix[0]*myMatrix[2]+rhs.myMatrix[1]*myMatrix[5]+rhs.myMatrix[2]*myMatrix[8];

		result.myMatrix[3] = rhs.myMatrix[3]*myMatrix[0]+rhs.myMatrix[4]*myMatrix[3]+rhs.myMatrix[5]*myMatrix[6];
		result.myMatrix[4] = rhs.myMatrix[3]*myMatrix[1]+rhs.myMatrix[4]*myMatrix[4]+rhs.myMatrix[5]*myMatrix[7];
		result.myMatrix[5] = rhs.myMatrix[3]*myMatrix[2]+rhs.myMatrix[4]*myMatrix[5]+rhs.myMatrix[5]*myMatrix[8];

		result.myMatrix[6] = rhs.myMatrix[6]*myMatrix[0]+rhs.myMatrix[7]*myMatrix[3]+rhs.myMatrix[8]*myMatrix[6];
		result.myMatrix[7] = rhs.myMatrix[6]*myMatrix[1]+rhs.myMatrix[7]*myMatrix[4]+rhs.myMatrix[8]*myMatrix[7];
		result.myMatrix[8] = rhs.myMatrix[6]*myMatrix[2]+rhs.myMatrix[7]*myMatrix[5]+rhs.myMatrix[8]*myMatrix[8];

		return result;
	}

	Vector3 operator*(Vector3& v) const
	{
		Vector3 result;

		result.x = myMatrix[0]*v.x + myMatrix[1]*v.y+ myMatrix[2]*v.z;
		result.y = myMatrix[3]*v.x + myMatrix[4]*v.y+ myMatrix[5]*v.z;
		result.z = myMatrix[6]*v.x + myMatrix[7]*v.y+ myMatrix[8]*v.z;
		
		return result;
	}

	Point3 operator*(Point3& p) const
	{
		Point3 result;
		
		result.x = myMatrix[0]*p.x + myMatrix[1]*p.y+ myMatrix[2]*p.z;
		result.x = myMatrix[3]*p.x + myMatrix[4]*p.y+ myMatrix[5]*p.z;
		result.x = myMatrix[6]*p.x + myMatrix[7]*p.y+ myMatrix[8]*p.z;
		
		return result;
	}
	Matrix33* inverse();
	Matrix33 Transpose();
};