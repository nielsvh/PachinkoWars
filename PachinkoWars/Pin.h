#pragma once
#include "Point3.h"

class Pin
{
public:
	Pin(void);
	Pin(Point3 myPosition);
	~Pin(void);
	Point3 position;
};

