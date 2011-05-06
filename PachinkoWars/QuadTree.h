#pragma once
#include <vector>
#include <gl/glut.h>
#include "GameObject.h"

using namespace std;

#define TOLERANCE 10
class QuadTree
{
private:
	class MyNode{
	public:
		MyNode(){
			tl = tr = bl = br = NULL;
		};
		MyNode(const MyNode& node)
		{
			this->tree = node.tree;
			this->myObjects = node.myObjects;
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
		QuadTree* tree;
		MyNode *tl, *tr, *bl, *br;
		vector<GameObject*>* myObjects;
		Point3 *position;
		float width, height;
	};
public:
	QuadTree(void);
	~QuadTree(void);
	void BuildStaticTree(vector<GameObject*> objects, Point3* location, float width, float height);
	void AddMovingObjects(vector<GameObject*> objects);
	void Draw();
private:
	vector<GameObject*> myObjects;

	MyNode *rootStatic, *rootNode;
	void SplitNode(MyNode* n, int steps);
	void Draw(MyNode* n);
};

