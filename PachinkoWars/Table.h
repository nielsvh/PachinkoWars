#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <gl/glut.h>
#include "texture.h"
#include "PinLineCurve.h"
#include "QuadTree.h"
#include "Ball.h"
using namespace std;

#define FILE_NAME "PACHINKO.txt"
#define STEPS 100

class Table
{
public:
	Table(void);
	~Table(void);
	void init();
	void FileIn();
	void Draw();
	void Update();
	void CreateSides(Point3 p1, Point3 p2, Point3 p3, Point3 p4, int* step);
	void createWall( Point3 p1, Point3 p2, Point3 p3, Point3 p4 );
	vector<Pin*> pins;
	vector<Ball*> balls;
	QuadTree tree;
	Vector3* fG;
	vector<GameObject*> objects;
	vector<Point3*> tableWallPoints;
};

