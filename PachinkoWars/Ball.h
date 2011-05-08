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
	Vector3 Velocity() const { return velocity; }
	void Velocity(Vector3 val) { velocity = val; }
private:
	Vector3* gravity;
	Vector3 velocity, acceleration;
};

