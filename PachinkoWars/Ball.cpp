#include "Ball.h"

Ball::Ball(void)
{
	velocity = Vector3();
	acceleration = Vector3();
}

Ball::Ball( Point3 pos )
{
	position = pos;
	radius = .2;
}


Ball::~Ball(void)
{
}

void Ball::Draw()
{
	//glPushMatrix();
	//glPopMatrix();

	//glLoadIdentity();

	glPushMatrix();
	/////////
	glTranslatef(position.x, position.y, 0);
	////////
	glutWireSphere(radius,10,10);
	glPopMatrix();
}
