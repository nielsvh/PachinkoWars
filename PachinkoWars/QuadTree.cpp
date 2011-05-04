#include "QuadTree.h"


QuadTree::QuadTree(void)
{
}


QuadTree::~QuadTree(void)
{
}

void QuadTree::BuildTree( vector<GameObject*> objects, Point3* location, float width, float height )
{
	
	rootNode = new MyNode();
	rootNode->myObjects = new vector<GameObject*>();
	myObjects = vector<GameObject*>();
	for (int i = 0; i<objects.size();i++)
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
	SplitNode(rootNode, 0);
}

void QuadTree::SplitNode( MyNode* n, int steps )
{
	if (steps>3)
	{
		return;
	}
	n->tl = new MyNode();n->tr = new MyNode();n->bl = new MyNode();n->br = new MyNode();

	float w = n->width/2.0, h = n->height/2.0;

	n->tl->width = n->tr->width = n->bl->width = n->br->width = w;
	n->tl->height = n->tr->height = n->bl->height = n->br->height = h;

	//n->tl-> n->tr-> = n->bl-> = n->br-> = ;
	n->tl->position = n->position;
	n->tr->position = new Point3(n->position->x+w, n->position->y, n->position->z);
	n->bl->position = new Point3(n->position->x, n->position->y-h, n->position->z);
	n->br->position = new Point3(n->position->x+w, n->position->y-h, n->position->z);

	n->tl->myObjects = new vector<GameObject*>();n->tr->myObjects = new vector<GameObject*>();n->bl->myObjects = new vector<GameObject*>();n->br->myObjects = new vector<GameObject*>();
	for (int i = 0;i<n->myObjects->size();i++)
	{
		if (myObjects[i]->position.x>=n->position->x+w)
		{
			if (myObjects[i]->position.y>=n->position->y-h)
			{
				n->br->myObjects->push_back(myObjects[i]);
			}
			else
			n->tr->myObjects->push_back(myObjects[i]);
		}
		else
		{
			if (myObjects[i]->position.y>=n->position->y-h)
			{
				n->bl->myObjects->push_back(myObjects[i]);
			}
			else
			n->tl->myObjects->push_back(myObjects[i]);
		}
	}
	// for now don't remove objects from parent nodes

	n->tl->tree = n->tr->tree = n->bl->tree = n->br->tree = this;
	
	if (n->tl->myObjects->size()>TOLERANCE)
	SplitNode(n->tl, ++steps);
	if (n->tr->myObjects->size()>TOLERANCE)
	SplitNode(n->tr, ++steps);
	if (n->bl->myObjects->size()>TOLERANCE)
		SplitNode(n->bl, ++steps);
	if (n->br->myObjects->size()>TOLERANCE)
		SplitNode(n->br, ++steps);

	return;
}

void QuadTree::Draw()
{
	if (rootNode != NULL)
		Draw(rootNode);
}

void QuadTree::Draw( MyNode* n )
{
	glBegin(GL_LINE_STRIP);
	glVertex3f(n->position->x, n->position->y,n->position->z);
	glVertex3f(n->position->x+n->width, n->position->y, n->position->z);
	glVertex3f(n->position->x+n->width, n->position->y-n->height, n->position->z);
	glVertex3f(n->position->x, n->position->y-n->height, n->position->z);
	glEnd();
	if (n->tr != NULL)
	{
		Draw(n->tl);
		Draw(n->tr);
		Draw(n->bl);
		Draw(n->br);
	}
}
