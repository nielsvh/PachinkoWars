#pragma once
#include "GameObject.h"
#include "Vector3.h"

class Ball:public GameObject
{
public:
	Ball(void);
	Ball(Point3 pos, Vector3* fG);
	~Ball(void);
	void Update();
	void Draw();
private:
	Vector3* gravity;
	float radius;
	Vector3 velocity, acceleration;
};

