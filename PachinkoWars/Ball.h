#pragma once
#include "GameObject.h"
#include "Vector3.h"

class Ball:public GameObject
{
public:
	Ball(void);
	Ball(Point3 pos);
	~Ball(void);
	void Draw();
private:
	float radius;
	Vector3 velocity, acceleration;
};

