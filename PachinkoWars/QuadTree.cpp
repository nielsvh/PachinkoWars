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
	if (steps>4)
	{
		return;
	}
	n->tl = new MyNode();
	n->tr = new MyNode();
	n->bl = new MyNode();
	n->br = new MyNode();

	float w = n->width/2.0, h = n->height/2.0;

	n->tl->width = n->tr->width = n->bl->width = n->br->width = w;
	n->tl->height = n->tr->height = n->bl->height = n->br->height = h;

	//n->tl-> n->tr-> = n->bl-> = n->br-> = ;
	n->bl->position = n->position;
	n->br->position = new Point3(n->position->x+w, n->position->y, n->position->z);

	n->tl->position = new Point3(n->position->x, n->position->y+h, n->position->z);
	n->tr->position = new Point3(n->position->x+w, n->position->y+h, n->position->z);

	n->tl->myObjects = new vector<GameObject*>();
	n->tr->myObjects = new vector<GameObject*>();
	n->bl->myObjects = new vector<GameObject*>();
	n->br->myObjects = new vector<GameObject*>();
	for (int i = 0;i<n->myObjects->size();i++)
	{
		GameObject* obj = (*n->myObjects)[i];
		if ((*n->myObjects)[i]->position.x >= n->tr->position->x)
		{
			if ((*n->myObjects)[i]->position.y >= n->tr->position->y)
			{
				n->tr->myObjects->push_back((*n->myObjects)[i]);
			}
			else
			{
				n->br->myObjects->push_back((*n->myObjects)[i]);
			}
		}
		else
		{
			if ((*n->myObjects)[i]->position.y >= n->tl->position->y)
			{
				n->tl->myObjects->push_back((*n->myObjects)[i]);
			}
			else
			{
				n->bl->myObjects->push_back((*n->myObjects)[i]);
			}
		}
	}
	// for now don't remove objects from parent nodes

	n->tl->tree = n->tr->tree = n->bl->tree = n->br->tree = this;
	
	if (n->tl->myObjects->size()>TOLERANCE)
		SplitNode(n->tl, steps+1);

	if (n->tr->myObjects->size()>TOLERANCE)
		SplitNode(n->tr, steps+1);

	if (n->bl->myObjects->size()>TOLERANCE)
		SplitNode(n->bl, steps+1);

	if (n->br->myObjects->size()>TOLERANCE)
		SplitNode(n->br, steps+1);
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
	glVertex3f(n->position->x+n->width, n->position->y+n->height, n->position->z);
	glVertex3f(n->position->x, n->position->y+n->height, n->position->z);
	glEnd();
	if (n->tr != NULL)
	{
		Draw(n->tl);
		Draw(n->tr);
		Draw(n->bl);
		Draw(n->br);
	}
}
