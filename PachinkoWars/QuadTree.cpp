#include "QuadTree.h"


QuadTree::QuadTree(void)
{
}


QuadTree::~QuadTree(void)
{
}

void QuadTree::BuildTree( GameObject* objects, int numPoints, Point3* location, float width, float height )
{
	
	rootNode = new MyNode();
	myObjects = vector<GameObject>();
	for (int i = 0; i<numPoints;i++)
	{
		//vector<GameObject>* myObjects;
		myObjects.push_back(objects[i]);
		rootNode->myObjects->push_back(objects[i]);
	}
	//QuadTree* tree;
	rootNode->tree = this;
	//float *width, *height;
	rootNode->width = width;
	rootNode->height = height;
	//Point3 *position;
	rootNode->position = location;
	SplitNode(rootNode);
}

void QuadTree::SplitNode( MyNode* n )
{
	if (n->myObjects->size()<TOLERANCE)
		return;

	n->tl = new MyNode();n->tr = new MyNode();n->bl = new MyNode();n->br = new MyNode();

	float w = n->width/2.0, h = n->height/2.0;

	n->tl->width = n->tr->width = n->bl->width = n->br->width = w;
	n->tl->height = n->tr->height = n->bl->height = n->br->height = h;

	//n->tl-> n->tr-> = n->bl-> = n->br-> = ;
	n->tl->position = n->position;
	n->tr->position = new Point3(n->position->x+w, n->position->y, n->position->z);
	n->bl->position = new Point3(n->position->x, n->position->y+h, n->position->z);
	n->br->position = new Point3(n->position->x+w, n->position->y+h, n->position->z);

	for (int i = 0;i<n->myObjects->size();i++)
	{
		if (myObjects[i].position.x>=w)
		{
			if (myObjects[i].position.y>=h)
			{
				n->br->myObjects->push_back(myObjects[i]);
				continue;
			}
			n->tr->myObjects->push_back(myObjects[i]);
		}
		else
		{
			if (myObjects[i].position.y>=h)
			{
				n->bl->myObjects->push_back(myObjects[i]);
				continue;
			}
			n->tl->myObjects->push_back(myObjects[i]);
		}
	}
	// for now don't remove objects from parent nodes

	n->tl->tree = n->tr->tree = n->bl->tree = n->br->tree = this;

	SplitNode(n->tr);SplitNode(n->tl);SplitNode(n->br);SplitNode(n->bl);
}

void QuadTree::Draw()
{
	Draw(rootNode);
}

void QuadTree::Draw( MyNode* n )
{

}
