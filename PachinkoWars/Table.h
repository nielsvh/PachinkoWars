#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <gl/glut.h>
#include "texture.h"
#include "PinLineCurve.h"
#include "QuadTree.h"
#include "Ball.h"
#include "Spinner.h"
#include "BallHole.h"
using namespace std;

#define FILE_NAME "PACHINKO.txt"
#define STEPS 100

class Table
{
public:
	Table(void);
	Table(const Table& t)
	{
		this->fG = t.fG;
	}
	~Table(void);
	void init();
	void FileIn();
	void Draw();
	void Update();
	void CreateSides(Point3 p1, Point3 p2, Point3 p3, Point3 p4, int* step);
	void createWall( Point3 p1, Point3 p2, Point3 p3, Point3 p4 );
	vector<Pin*> pins;
	vector<Spinner*> spinners;
	vector<Ball*> balls;
	vector<BallHole*> holes;
	vector<GameObject*> movingObjects;
	QuadTree tree;
	Vector3* fG;
	vector<GameObject*> objects;
	vector<Point3*> tableWallPoints;
	static Table* thisTable;
	void SpawnBall();

	static void keyboardS (int key, int x, int y)
	{
		switch(key)
		{
		case GLUT_KEY_DOWN:
			thisTable->fG->y = -.005;
			break;
		case GLUT_KEY_UP:
			thisTable->fG->y = .005;
			break;
		case GLUT_KEY_RIGHT:
			break;
		case GLUT_KEY_LEFT:
			break;
		default:
			break;
		}
	}

	static void keyboardN(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case 27:
		case 'Q':
		case 'q':
			exit(0);
			break;
		case ' ':
			thisTable->SpawnBall();
			break;
		}
	}
};