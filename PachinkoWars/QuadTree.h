#pragma once
#include <vector>
#include <gl/glut.h>
#include "GameObject.h"

#include "Pin.h"
#include "Ball.h"
#include "Spinner.h"
#include "Plane.h"

using namespace std;

#define TOLERANCE 10
class QuadTree
{
private:
	class MyNode{
	public:
		MyNode(){
			tl = tr = bl = br = NULL;
			hasBall = hasWall = false;
		};
		MyNode(const MyNode& node)
		{
			hasBall = false;
			hasWall = node.hasWall;
			this->tree = node.tree;
			this->myObjects = new vector<GameObject*>(*node.myObjects);
			this->wallPoints = vector<Point3*>(node.wallPoints);
			this->position = node.position;
			this->width = node.width;
			this->height = node.height;
			if (node.tl != NULL)
			{
			this->tl = new MyNode(*node.tl);
			this->tr = new MyNode(*node.tr);
			this->bl = new MyNode(*node.bl);
			this->br = new MyNode(*node.br);
			}
			else{
				this->tl = this->tr = this->bl = this->br = NULL;
			}
		}
		bool hasBall, hasWall;
		QuadTree* tree;
		MyNode *tl, *tr, *bl, *br;
		vector<GameObject*>* myObjects;
		vector<Point3*> wallPoints;
		Point3 *position;
		float width, height;
	};
public:
	QuadTree(void);
	~QuadTree(void);
	void BuildStaticTree(vector<GameObject*> objects, Point3* location, float width, float height);
	void AddTableWalls(vector<Point3*> points);
	void AddMovingObjects(vector<GameObject*> objects);
	void InsertObject( GameObject* obj, MyNode* n, int steps );
	void Draw();
	void CheckCollisions();
	void BruteCollisions(vector<Pin*> pins, vector<Ball*> balls);
private:
	vector<GameObject*> objects;
	void AddTableWalls( Point3 *p, MyNode* n );
	MyNode *rootStatic, *rootNode;
	void SplitNode(MyNode* n, int steps);
	void Draw(MyNode* n);
	void CheckCollisionsNode(MyNode* n);
};

