#include "Matrix33.h"


Matrix33::Matrix33(void)
{
	myMatrix = new float[9];
	for (int i = 0;i<9;i++)
	{
		myMatrix[i] = 0;
	}
}

Matrix33::Matrix33(const Quaternion& q)
{
	myMatrix = new float[9];

	float s, xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;

	s = 2.0f/(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);

	xs = s*q.x;		ys = s*q.y;		zs = s*q.z;
	wx = q.w*xs;	wy = q.w*ys;	wz = q.w*zs;
	xx = q.x*xs;	xy = q.x*ys;	xz = q.x*zs;
	yy = q.y*ys;	yz = q.y*zs;	zz = q.z*zs;

	myMatrix[0] = 1.0f - (yy + zz);
	myMatrix[3] = xy-wz;
	myMatrix[6] = xz+wy;

	myMatrix[1] = xy+wz;
	myMatrix[4] = 1.0f-(xx-zz);
	myMatrix[7] = yz-wx;

	myMatrix[2] = xz - wy;
	myMatrix[5] = yz+wx;
	myMatrix[8] = 1.0f - (xx+yy);
}


Matrix33::~Matrix33(void)
{
}

Matrix33* Matrix33::inverse()
{
	//a11(a33a22-a32a23)-a21(a33a12-a32a13)+a31(a23a12-a22a13)
	float det = myMatrix[0]*(myMatrix[8]*myMatrix[4]-myMatrix[7]*myMatrix[5])
		-myMatrix[3]*(myMatrix[8]*myMatrix[1]-myMatrix[7]*myMatrix[2])
		+myMatrix[6]*(myMatrix[5]*myMatrix[1]-myMatrix[4]*myMatrix[2]);

	/*|   a33a22-a32a23  -(a33a12-a32a13)   a23a12-a22a13  |
	| -(a33a21-a31a23)   a33a11-a31a13  -(a23a11-a21a13) |
	|   a32a21-a31a22  -(a32a11-a31a12)   a22a11-a21a12  |*/
	Matrix33* newMatrixx = new Matrix33();
	newMatrixx->myMatrix[0] = det*(myMatrix[8] *myMatrix[4]-myMatrix[7]* myMatrix[5]);
	newMatrixx->myMatrix[1] = det*(-(myMatrix[8]* myMatrix[1]-myMatrix[7]* myMatrix[2]));
	newMatrixx->myMatrix[2] = det*(myMatrix[5] *myMatrix[1] - myMatrix[4] *myMatrix[2]);
	newMatrixx->myMatrix[3] = det*(-(myMatrix[8]* myMatrix[3] - myMatrix[6]* myMatrix[5]));
	newMatrixx->myMatrix[4] = det*(myMatrix[8] *myMatrix[0]-myMatrix[6] *myMatrix[2]);
	newMatrixx->myMatrix[5] = det*(-(myMatrix[5]* myMatrix[0]-myMatrix[3]* myMatrix[2]));
	newMatrixx->myMatrix[6] = det*(myMatrix[7] *myMatrix[3] - myMatrix[6] *myMatrix[4]);
	newMatrixx->myMatrix[7] = det*(-(myMatrix[7]* myMatrix[0] - myMatrix[6]* myMatrix[2]));
	newMatrixx->myMatrix[8] = det*(myMatrix[4] *myMatrix[0] -myMatrix[3] *myMatrix[1]);
	return newMatrixx;
}

Matrix33 Matrix33::Transpose()
{
	//0 1 2
	//3 4 5
	//6 7 8

	//0 3 6
	//1 4 7
	//2 5 8

	Matrix33 m = Matrix33();
	m.myMatrix[0] = this->myMatrix[0];
	m.myMatrix[1] = this->myMatrix[3];
	m.myMatrix[2] = this->myMatrix[6];
	m.myMatrix[3] = this->myMatrix[1];
	m.myMatrix[4] = this->myMatrix[4];
	m.myMatrix[5] = this->myMatrix[7];
	m.myMatrix[6] = this->myMatrix[2];
	m.myMatrix[7] = this->myMatrix[5];
	m.myMatrix[8] = this->myMatrix[8];

	return m;
}
