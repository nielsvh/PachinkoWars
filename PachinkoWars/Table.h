#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <gl/glut.h>
#include "texture.h"
#include "PinLineCurve.h"
#include "QuadTree.h"
using namespace std;

#define fileName "PACHINKO.txt"

class Table
{
public:
	Table(void);
	~Table(void);
	void init();
	void FileIn();
	void Draw();
	void Update();
	vector<Pin*> pins;
	QuadTree tree;
};

