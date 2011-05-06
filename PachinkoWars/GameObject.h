#pragma once
#include "Vector3.h"
class GameObject
{
public:
	enum type{BALL, PIN};
	GameObject(void);
	~GameObject(void);
	Point3 position;
	float radius;
	type objectType;
	bool isColliding;
};

