#include "QuadTree.h"


QuadTree::QuadTree(void)
{
	rootStatic = rootNode = NULL;
}


QuadTree::~QuadTree(void)
{
}

void QuadTree::BuildStaticTree( vector<GameObject*> objects, Point3* location, float width, float height )
{

	rootStatic = new MyNode();
	rootStatic->myObjects = new vector<GameObject*>();
	//myObjects = vector<GameObject*>();
	for (int i = 0; i<objects.size();i++)
	{
		//myObjects.push_back(objects[i]);
		rootStatic->myObjects->push_back(objects[i]);
	}

	rootStatic->tree = this;
	rootStatic->width = width;
	rootStatic->height = height;
	rootStatic->position = location;
	SplitNode(rootStatic, 0);
}

void QuadTree::SplitNode( MyNode* n, int steps )
{
	if (steps>4 || n->myObjects->size() < TOLERANCE)
	{
		for (int i = 0;i<n->myObjects->size();i++)
		{
			if ((*n->myObjects)[i]->objectType == GameObject::type::BALL)
			{
				n->hasBall = true;
				break;
			}
			else
			{
				n->hasBall = false;
			}
		}
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

		SplitNode(n->tl, steps+1);

		SplitNode(n->tr, steps+1);

		SplitNode(n->bl, steps+1);

		SplitNode(n->br, steps+1);
}

void QuadTree::AddMovingObjects( vector<GameObject*> objects )
{
	rootNode = new MyNode(*rootStatic);
	for (int i = 0; i<objects.size();i++)
	{
		// for each object to be added, find the node that it belongs in
		InsertObject(objects[i], rootNode,0);
	}
}

void QuadTree::InsertObject( GameObject* obj, MyNode* n, int steps )
{
	if (n->tl == NULL)
	{
		// after all the objects have been added, split the nodes based off of their depth and number of object inside.
		//n->hasBall = true;
		n->myObjects->push_back(obj);
		SplitNode(n,steps);
		return;
	}

	if (obj->position.x > n->br->position->x || obj->position.x + obj->radius > n->br->position->x)
	{
		if (obj->position.y > n->tr->position->y|| obj->position.y + obj->radius > n->tr->position->y)
		{
			InsertObject(obj,n->tr, steps+1);
		}

		if (obj->position.y < n->tr->position->y|| obj->position.y - obj->radius < n->tr->position->y)
		{
			InsertObject(obj,n->br, steps+1);
		}
	}
	

	if (obj->position.x < n->br->position->x || obj->position.x - obj->radius < n->br->position->x)
	{
		if (obj->position.y > n->tr->position->y|| obj->position.y + obj->radius > n->tr->position->y)
		{
			InsertObject(obj,n->tl, steps+1);
		}
		if (obj->position.y < n->tr->position->y|| obj->position.y - obj->radius < n->tr->position->y)
		{
			InsertObject(obj, n->bl, steps+1);
		}
	}
}

void QuadTree::Draw()
{
	if (rootNode != NULL)
		Draw(rootNode);
}

void QuadTree::BruteCollisions(vector<Pin*> pins, vector<Ball*> balls)
{
	// check collisions with objects
	for (int i = 0;i<balls.size();i++)
	{
		for (int j = 0;j<pins.size();j++)
		{
			//			if (i == j)
			//continue;
			Vector3 diff = balls[i]->position-pins[j]->position;
			float minDist = balls[i]->radius+pins[j]->radius;
			if (diff.getLength()<minDist)
			{
				if (pins[j]->objectType ==  GameObject::type::BALL)
				{

				}
				else if (pins[j]->objectType ==  GameObject::type::PIN)
				{
					Vector3 newV = diff;
					newV.normalize();
					newV = (balls[i])->Velocity().getLength() * newV;
					(balls[i])->Velocity(newV);
				}

			}
		}
	}
}

void QuadTree::CheckCollisions()
{
	CheckCollisionsNode(rootNode);
}

void QuadTree::CheckCollisionsNode(MyNode* n)
{
	if (n->bl != NULL)
	{
		CheckCollisionsNode(n->bl);
		CheckCollisionsNode(n->tl);
		CheckCollisionsNode(n->br);
		CheckCollisionsNode(n->tr);
		return;
	}
	else if (!n->hasBall)
	{
		return;
	}
	else if(n->myObjects->size()<2)//Only contains the ball
	{
		return;
	}

	// check collisions with objects
	for (int i = 0;i<n->myObjects->size();i++)
	{
		if ((*n->myObjects)[i]->objectType !=  GameObject::type::BALL)
		{
			continue;
		}
		for (int j = 0;j<n->myObjects->size();j++)
		{
//			if (i == j)
				//continue;
			Vector3 diff = (*n->myObjects)[i]->position-(*n->myObjects)[j]->position;
			float minDist = (*n->myObjects)[i]->radius+(*n->myObjects)[j]->radius;
			if (diff.getLength()<minDist)
			{
				if ((*n->myObjects)[j]->objectType ==  GameObject::type::BALL)
				{

				}
				else if ((*n->myObjects)[j]->objectType ==  GameObject::type::PIN)
				{
					Vector3 newV = diff;
					newV.normalize();
					(*n->myObjects)[i]->position = (*n->myObjects)[j]->position + (minDist * newV); 
					newV = ((Ball*)(*n->myObjects)[i])->Velocity().getLength() * .7 * newV;
					((Ball*)(*n->myObjects)[i])->Velocity(newV);
				}

			}
		}
	}

	// check collisions with walls!
	if (n->hasWall)
	{
		for (int i = 0;i<n->myObjects->size();i++)
		{
			if ((*n->myObjects)[i]->objectType == GameObject::type::BALL)
			{
				for (int j = 0;j<n->wallPoints.size()-1;j++)
				{
					Vector3 v = *n->wallPoints[j+1] - *n->wallPoints[j];
					Vector3 v2 = (*n->myObjects)[i]->position - *n->wallPoints[j];

					if (v*v2<0)
					{
						printf("outside bounds.\n");
					}

					// get the projection!
					Vector3 tmp = v;
					tmp.normalize();
					Vector3 proj = (v2*tmp)*tmp;

					if (v*v2 >0 && proj.getLength()< v.getLength())
					{
						printf("The length of |v|: %f\n", tmp.getLength());
						printf("The dot product of proj*v: %f\n",proj*v);
						Vector3 norm = v.cross(Vector3(0,0,-1));
						norm.normalize();
						printf("Is the normal perpendicular: %f %f\n",v*norm, proj*norm);
						if ((v2 - proj).getLength() <= (*n->myObjects)[i]->radius)
						{
							printf("Ball's old position x:%f y:%f z:%f\n",(*n->myObjects)[i]->position.x ,(*n->myObjects)[i]->position.y ,(*n->myObjects)[i]->position.z );
							printf("Ball's calculated new position x:%f y:%f z:%f\n",(*n->wallPoints[j] + proj + ((*n->myObjects)[i]->radius *norm)).x,(*n->wallPoints[j] + proj + ((*n->myObjects)[i]->radius *norm)).y,(*n->wallPoints[j] + proj + ((*n->myObjects)[i]->radius *norm)).z);
							(*n->myObjects)[i]->position = *n->wallPoints[j] + proj + ((*n->myObjects)[i]->radius *norm);
							((Ball*)(*n->myObjects)[i])->Velocity(-1*((Ball*)(*n->myObjects)[i])->Velocity());
						}
					}
				}
			}
		}
	}
}

void QuadTree::Draw( MyNode* n )
{
	if (n->hasBall == true)
	{
		glColor3f(1,0,0);
	}
	else
	{
		glColor3f(1,1,1);
	}
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

void QuadTree::AddTableWalls( vector<Point3*> points )
{
	for (int i = 0;i<points.size();i++)
	{
		AddTableWalls(points[i], rootStatic);
	}
}

void QuadTree::AddTableWalls( Point3 *p, MyNode* n )
{
	// if it is null, then it is a leaf, not a node. Add to leaf!
	if (n->tl != NULL)
	{
		if (p->x > n->br->position->x)
		{
			if (p->y> n->tl->position->y)
			{
				AddTableWalls(p, n->tr);
				return;
			}
			AddTableWalls(p, n->br);
			return;
		}
		else
		{
			if (p->y> n->tl->position->y)
			{
				AddTableWalls(p, n->tl);
				return;
			}
			AddTableWalls(p, n->bl);
			return;
		}
	}

	n->hasWall = true;
	n->wallPoints.push_back(p);
}