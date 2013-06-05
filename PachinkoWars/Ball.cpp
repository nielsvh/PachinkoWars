#include "Ball.h"

Ball::Ball(void)
{
	velocity = Vector3();
	acceleration = Vector3();
}

Ball::Ball( Point3 pos, Vector3* fG,float m)
{
	position = pos;
	mass = m;
	radius = .15;
	gravity = fG;
	objectType = type::BALL;
	toDelete = false;
}


Ball::~Ball(void)
{
}

void Ball::Update()
{
	if (!toDelete)
	{
	acceleration = *gravity;
	velocity = velocity+*gravity;
	position = position + velocity;
	}
}

void Ball::Draw()
{
	//glPushMatrix();
	//glPopMatrix();

	//glLoadIdentity();

	glColor3f(1,1,1);
	glPushMatrix();
	/////////
	glTranslatef(position.x, position.y, 0);
	////////
	glutWireSphere(radius,10,10);
	glPopMatrix();
}
