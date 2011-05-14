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
	rootStatic->wallPoints = new vector<Point3*>();
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

	n->tl->wallPoints = n->wallPoints;
	n->tr->wallPoints = n->wallPoints;
	n->bl->wallPoints = n->wallPoints;
	n->br->wallPoints = n->wallPoints;

	n->tl->hasWall = n->hasWall;
	n->tr->hasWall = n->hasWall;
	n->bl->hasWall = n->hasWall;
	n->br->hasWall = n->hasWall;
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
		n->hasBall = true;
		n->myObjects->push_back(obj);
		//SplitNode(n,steps);
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
	delete(rootNode);
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
	else if(n->myObjects->size()<2 && !n->hasWall)//Only contains the ball
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
			if (i == j)
			continue;

			Vector3 diff = (*n->myObjects)[i]->position-(*n->myObjects)[j]->position;
			float minDist = (*n->myObjects)[i]->radius+(*n->myObjects)[j]->radius;
			if (diff.getLength()<minDist)
			{
				if ((*n->myObjects)[j]->objectType ==  GameObject::type::BALL)
				{
					Vector3 newV = diff;
					newV.normalize();
					Vector3 tmpV = minDist * newV;
					(*n->myObjects)[i]->Position((*n->myObjects)[j]->position + tmpV);
					newV = ((Ball*)(*n->myObjects)[i])->Velocity().getLength() * .7 * newV;
					((Ball*)(*n->myObjects)[i])->Velocity(newV);
				}
				else if ((*n->myObjects)[j]->objectType ==  GameObject::type::PIN)
				{
					Vector3 newV = diff;
					newV.normalize();
					Vector3 tmpV = minDist * newV;
					(*n->myObjects)[i]->Position((*n->myObjects)[j]->position + tmpV);
					newV = ((Ball*)(*n->myObjects)[i])->Velocity().getLength() * .7 * newV;
					// to prevent the balls from getting stuck on the top of pins, we add just a little to the x in velocity.
					newV = newV + Vector3(.001,0,0);
					((Ball*)(*n->myObjects)[i])->Velocity(newV);
				}
				else if ((*n->myObjects)[j]->objectType ==  GameObject::type::SPINNER)
				{
					Ball* b = (Ball*)(*n->myObjects)[i];
					Spinner* s = (Spinner*)(*n->myObjects)[j];
					float bEnergy = .5 * b->Mass() * b->Velocity() * b->Velocity();

					// need to check p1, then p2 and p4 or p3, then p2 and p4
					Vector3 vTemp = (Vector3&)(b->position - s->boundingCube[0]);
					float dist = vTemp.getLength();
					//printf("Dist:%f s.x:%f s.y:%f b.x:%f b.y:%f\n",dist,s->boundingCube[0].x,s->boundingCube[0].y,b->Position().x, b->Position().y);
					int index = 0;
					for (int i=1;i < 8;i++)
					{
						Vector3 v = (Vector3&)(b->position - s->boundingCube[i]);
						float newDist = v.getLength();
						if(dist > newDist)
						{
							dist = newDist;
							index = i;
						}
					}

					Vector3 closest = s->boundingCube[index] - s->position;
					Vector3 tempV = diff;
					tempV.normalize();
					Vector3 proj = (closest*tempV)*tempV;
					float temp = proj.getLength();
					if(diff.getLength() > temp + b->radius)
					{
						continue;
					}

					// find the current position of the bar
					float angle = 1.0;
					Quaternion qsdf = Quaternion(Vector3::zAxis,angle);
					s->Rotation(qsdf);
					// find the force applied to the bar
					// ft = dp/dt = m*dv/dt
					// find perpendicular momentum
					Vector3 totalForce = bEnergy * b->Velocity();


					// t = r X F
					Vector3 torque = diff.cross(totalForce);

					Vector3 dL = .05 * torque;

					// find the rotation matrix and the inverse of the rotation matrix
					Matrix33 myRotation = Matrix33(s->Rotation());
					Matrix33 myRotationT = myRotation.Transpose();

					s->MyL(s->MyL() + dL);

					//w(i+1) = q(i+1) * I(-1) * qT(i+1) * L(i+1)
					s->AngularVel(myRotation * *s->Tensor()->inverse() * myRotationT * s->MyL());

					//q(n+1) = q(n) + h(.5 * w(n)*q(n))
					s->Rotation(s->Rotation() + .05*(.5 * Quaternion(s->AngularVel()) * s->Rotation()));
					Quaternion q = s->Rotation();
					q.normalize();
					s->Rotation(q);
				}
				else if ((*n->myObjects)[j]->objectType ==  GameObject::type::HOLE)
				{
					Ball *b = (Ball*)(*n->myObjects)[i];
					BallHole *h = (BallHole*)(*n->myObjects)[j];
					Vector3 vTemp = diff;
					vTemp.normalize();

					float hRad = vTemp.y*h->width + vTemp.x*h->height;
					if (hRad + b->radius <= diff.getLength())
					{
						b->toDelete = true;
					}
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
				Ball* b = (Ball*)(*n->myObjects)[i];
				for (int j = 0;j<n->wallPoints->size()-1;j++)
				{
					Vector3 wall = *(*n->wallPoints)[j+1] - *(*n->wallPoints)[j];
					/*
					// get position of ball, relative to line
					var x1:Number = ball.x - line.x;
					var y1:Number = ball.y - line.y;
					*/
					Vector3 ballFromWall = b->position - *(*n->wallPoints)[j];

					// check to see if the ball will collide with line
					Vector3 rej = rejection(ballFromWall,wall);
					if (rej.getLength() <= b->radius)
					{
						// check to see if the ball is above or below the line and check to see if it is heading towards or away from line
						Plane p = Plane(*(*n->wallPoints)[j], *(*n->wallPoints)[j+1], Point3(0,0,1));
						float relativePosition = p.normal * ballFromWall;
						float relativeDirection = p.normal * b->Velocity();
						if ((relativePosition > 0 && relativeDirection < 0) || (relativePosition < 0 && relativeDirection > 0))
						{
							/*
							// get angle, sine and cosine
							var angle:Number = line.rotation * Math.PI / 180;
							var cos:Number = Math.cos(angle);
							var sin:Number = Math.sin(angle);
							*/
							float theta, c, s;
							theta = acos((wall * Vector3(1,0,0))/wall.getLength());
							if (b->position.x<0)
							{
								theta *= -1;
							}
							c = cos(theta), s = sin(theta);


							/*
							// rotate coordinates
							var y2:Number = cos * y1 - sin * x1;

							// rotate velocity
							var vy1:Number = cos * ball.vy - sin * ball.vx;

							// rotate coordinates
							var x2:Number = cos * x1 + sin * y1;

							// rotate velocity
							var vx1:Number = cos * ball.vx + sin * ball.vy;

							y2 = -ball.height / 2;
							vy1 *= bounce;

							// rotate everything back;
							x1 = cos * x2 - sin * y2;
							y1 = cos * y2 + sin * x2;
							ball.vx = cos * vx1 - sin * vy1;
							ball.vy = cos * vy1 + sin * vx1;
							ball.x = line.x + x1;
							ball.y = line.y + y1;
							*/
							Vector3 position2;
							Vector3 velocityRot;

							position2 = Vector3(c * ballFromWall.x + s * ballFromWall.y,
								c * ballFromWall.y - s * ballFromWall.x,
								0);
							velocityRot = Vector3( c * b->Velocity().x + s * b->Velocity().y,
								c * b->Velocity().y - s * b->Velocity().x,
								0);

							// set the ball outside the wall
							position2.y = b->radius;
							velocityRot.y *= -1;

							ballFromWall = Vector3(c * position2.x - s * position2.y,c * position2.y + s * position2.x,0);
							b->Velocity(Vector3(c * velocityRot.x - s * velocityRot.y,c * velocityRot.y + s * velocityRot.x,0));
							b->position = *(*n->wallPoints)[j] + ballFromWall;
						}


					}
					//delete(rej);

					//// get the projection!
					//Vector3 tmp = v;
					//tmp.normalize();
					//// get that funky projection, white boy
					//Vector3 proj = *project(v2,tmp);

					//// if the ball is in front of the start and behind the end, then it could collide.
					//if (v*v2 >0 && proj.getLength()< v.getLength())
					//{
					//	Plane plane = Plane(*n->wallPoints[j],*n->wallPoints[j+1],Point3((*n->wallPoints[j]).x,(*n->wallPoints[j]).y,-1));
					//	float rejections = rejection(v2, tmp)->getLength();
					//	if (rejections <= b->radius)
					//	{
					//		b->position = *n->wallPoints[j] + proj + (b->radius * 1.1f * plane.normal);
					//		
					//		float vel = b->Velocity().getLength();
					//		// COSS IS WRONG, FIX THIS THING!
					//		//float coss = (Vector3(1,0,0) * plane.normal);
					//		float coss = v * v2 * 1.0f/(v.getLength()*v2.getLength());

					//		float theta = acos(coss);
					//		/*if (b->position.x>0)
					//		{
					//			theta =  acos(coss) + 3.14159/2.0;
					//		}
					//		else{
					//			theta =  acos(coss) - 3.14159/2.0;
					//		}*/
					//		float c = cos(theta), s = sin(theta);

					//		Vector3 velP = c * b->Velocity(), velN = -1 * s * b->Velocity();

					//		float vpx = c * vel - s * velN.getLength(), vpy = s * vel + c*velN.getLength();
					//		
					//		Vector3 newv = Vector3(vpx, vpy, 0);
					//		newv.normalize();
					//		
					//		b->Velocity(vel * newv);
					//	}
					//}
				}
			}
		}
	}
}

void QuadTree::Draw()
{
	if (rootNode != NULL)
		Draw(rootStatic);
}

void QuadTree::Draw( MyNode* n )
{
	if (n->hasBall == true)
	{
		glColor3f(1,0,0);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i<n->wallPoints->size()-1 && n->wallPoints->size() != 0;i++)
		{
			glVertex3f((*n->wallPoints)[i]->x, (*n->wallPoints)[i]->y, 0);
			Plane plane = Plane(*(*n->wallPoints)[i],*(*n->wallPoints)[i+1],Point3((*n->wallPoints)[i]->x,(*n->wallPoints)[i]->y,-1));
			glVertex3f((*n->wallPoints)[i]->x + plane.normal.x, (*n->wallPoints)[i]->y + plane.normal.y, 0);
		}
		glEnd();
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
	float toleranceD = .15;
	// if it is null, then it is a leaf, not a node. Add to leaf!
	if (n->tl != NULL)
	{
		if (p->x > n->br->position->x || p->x + toleranceD > n->br->position->x)
		{
			if (p->y> n->tr->position->y || p->y + toleranceD> n->tr->position->y)
			{
				AddTableWalls(p, n->tr);
			}
			if (p->y< n->tr->position->y || p->y-toleranceD< n->tr->position->y)
			{
				AddTableWalls(p, n->br);
			}
		}
		if (p->x < n->br->position->x || p->x - toleranceD < n->br->position->x)
		{
			if (p->y> n->tl->position->y || p->y + toleranceD> n->tl->position->y)
			{
				AddTableWalls(p, n->tl);
			}
			if (p->y< n->tl->position->y || p->y-toleranceD< n->tl->position->y)
			{
				AddTableWalls(p, n->bl);
			}
		}
		return;
	}

	n->hasWall = true;
	n->wallPoints->push_back(p);
}