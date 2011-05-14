#pragma once
#include "Vector3.h"
class GameObject
{
public:
	enum type{BALL, PIN, SPINNER, HOLE};
	GameObject(void);
	~GameObject(void);
	Point3 position;
	Point3 Position() const { return position; }
	void Position(Point3 val) { position = val; }
	float radius;
	type objectType;
	bool isColliding;
};

