#pragma once
#include <vector>
#include <gl/glut.h>
#include "GameObject.h"

using namespace std;

#define TOLERANCE 10
class QuadTree
{
private:
	struct MyNode{
		QuadTree* tree;
		MyNode *tl, *tr, *bl, *br;
		vector<GameObject>* myObjects;
		Point3 *position;
		float width, height;
	};
public:
	QuadTree(void);
	~QuadTree(void);
	void BuildTree(GameObject* objects, int numPoints, Point3* location, float width, float height);

	void Draw();
private:
	vector<GameObject> myObjects;

	MyNode* rootNode;
	void SplitNode(MyNode* n);
	void Draw(MyNode* n);
};

