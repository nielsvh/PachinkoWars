#include "Ball.h"

Ball::Ball(void)
{
	velocity = Vector3();
	acceleration = Vector3();
}

Ball::Ball( Point3 pos, Vector3* fG )
{
	position = pos;
	radius = .2;
	gravity = fG;
}


Ball::~Ball(void)
{
}

void Ball::Update()
{
	acceleration = *gravity;
	velocity = velocity+*gravity;
	position = position + velocity;
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
