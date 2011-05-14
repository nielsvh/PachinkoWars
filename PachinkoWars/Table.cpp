#include "Table.h"

float xs[1000], ys[1000];
int xp = 0, yp = 0;
Table* Table::thisTable;

Table::Table(void)
{
	init();
}

Table::~Table(void)
{
}

void Table::init()
{
	// set the force of gravity so that all things in the board can reference it
	fG = new Vector3(0,-.005,0);

	// set up the pin and ball vectors
	pins = vector<Pin*>();
	spinners = vector<Spinner*>();
	balls = vector<Ball*>();
	holes = vector<BallHole*>();
	holes.push_back(new BallHole(Point3(0,.5,0),.5,1));
	//balls.push_back(new Ball(Point3(0,2.5,0), fG, 1));// TEST BALL

	//////////////////////////////////////////////////////////////////////////
	// Setup rendering for a texture.
	//////////////////////////////////////////////////////////////////////////
	//glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);


	int width, height;
	int nComponents;
	void* pTextureImage, *pTextureImage1;
	pTextureImage = read_texture("pachinko.rgb", &width, &height, &nComponents);
	glBindTexture(GL_TEXTURE_2D, 0);
	gluBuild2DMipmaps(GL_TEXTURE_2D,     // texture to specify
		GL_RGBA,           // internal texture storage format
		width,             // texture width
		height,            // texture height
		GL_RGBA,           // pixel format
		GL_UNSIGNED_BYTE,	// color component format
		pTextureImage);    // pointer to texture image

	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);


	// read in the object file. This flat file contains all of the board objects original positions.
	FileIn();

	// setup the quadtree
	tree = QuadTree();

	// insert the objects from the board into the quadtree
	objects = vector<GameObject*>(pins.begin(), pins.end());
	objects.insert(objects.end(), spinners.begin(), spinners.end());
	objects.insert(objects.end(), holes.begin(), holes.end());
	tree.BuildStaticTree(objects, new Point3(-8, 0, 0), 16.0, 16.0);
	tree.AddTableWalls(tableWallPoints);
}

void Table::FileIn()
{
	string line;
	fstream file;
	int *step = new int(0);

	file.open(FILE_NAME);
	//Tests to see if file was found
	if (!file)
	{
		cout << "Unable to open file\n";
		//exit(1); // File could not be found, no points, exit the program
	}

	// the x and y of the start and end of a line as well as the vectors for curves
	float x1,x2,x3,x4,y1,y2,y3,y4;
	Point3 p1, p2, p3, p4;
	vector<Pin*> tmpp;
	int wallPoint = 0;

	for(int i = 0; !file.eof(); i++){

		getline(file, line);

		if (line.length() == 0)
		{
			continue;
		}
		// lines start with the identifier of the object being described.
		// 'c' is for curves. Curves have four parts. p1, and p4 are the start and end of the curve. p2 and p4 are the points that describe the curve
		// and example curve is 'c10 20 20 30 30 40 40 50'
		// 'l' is for lines. Lives have two parts. p1 and p2 define the start and end of the line.
		// an example curve is 'l10 20 20 30'
		// 's' is for spinners. Spinners have a location, a radius, and a mass.
		// an example spinner is 's10 10 20 30' ( a spinner at 10,10 with a radius of 20 and a mass of 30)
		// all locations are based off of a 160/160 board. This makes the scale from board point to game point a ratio of 10.
		// the board is mirrored for now, so all the points are read in an mirrored.
		if (line[0] == 'c')
		{

			//// step through line string and get the point info
			string tmp = line.substr(1,line.length()-1);
			char * pch = strtok ((char*)tmp.c_str()," ");

			x1 = atof(pch);
			pch = strtok (NULL, " ");

			y1 = atof(pch);
			pch = strtok (NULL, " ");

			x2 = atof(pch);
			pch = strtok (NULL, " ");

			y2 = atof(pch);
			pch = strtok (NULL, " ");

			x3 = atof(pch);
			pch = strtok (NULL, " ");

			y3 = atof(pch);
			pch = strtok (NULL, " ");

			x4 = atof(pch);
			pch = strtok (NULL, " ");

			y4 = atof(pch);

			// set to game point
			xs[xp++] = (x1)/10.;
			xs[xp++] = (x2)/10.;
			xs[xp++] = (x3)/10.;
			xs[xp++] = (x4)/10.;
			ys[yp++] = (y1)/10.;
			ys[yp++] = (y2)/10.;
			ys[yp++] = (y3)/10.;
			ys[yp++] = (y4)/10.;

			// add the point
			tmpp = PinLineCurve::GetCurvePins(Point3(x1/10., y1/10.,0), Point3(x2/10., y2/10.,0),Point3(x3/10., y3/10.,0),Point3(x4/10., y4/10.,0));
			pins.insert(pins.end(),tmpp.begin(), tmpp.end());
			// mirror the point
			tmpp = PinLineCurve::GetCurvePins(Point3(-x1/10., y1/10.,0), Point3(-x2/10., y2/10.,0),Point3(-x3/10., y3/10.,0),Point3(-x4/10., y4/10.,0));
			pins.insert(pins.end(),tmpp.begin(), tmpp.end());
		}
		else if (line[0] == 'l')
		{
			// step through line string and get the point info
			string tmp = line.substr(1,line.length()-1);
			char * pch = strtok ((char*)tmp.c_str()," ");

			x1 = atof(pch);
			pch = strtok (NULL, " ");

			y1 = atof(pch);
			pch = strtok (NULL, " ");

			x2 = atof(pch);
			pch = strtok (NULL, " ");

			y2 = atof(pch);

			// set to game point
			xs[xp++] = x1/10.;
			xs[xp++] = x2/10.;
			ys[yp++] = y1/10.;
			ys[yp++] = y2/10.;

			// add to board
			tmpp = PinLineCurve::GetLinePins(Point3(x1/10.f, y1/10.f,0), Point3(x2/10.f, y2/10.f,0));
			pins.insert(pins.end(),tmpp.begin(), tmpp.end());
			// mirror
			tmpp = PinLineCurve::GetLinePins(Point3(-x1/10.f, y1/10.f,0), Point3(-x2/10.f, y2/10.f,0));
			pins.insert(pins.end(),tmpp.begin(), tmpp.end());
		}
		else if (line[0] == 's')
		{
			// step through line string and get the point info
			string tmp = line.substr(1,line.length()-1);
			char * pch = strtok ((char*)tmp.c_str()," ");

			x1 = atof(pch);
			pch = strtok (NULL, " ");

			y1 = atof(pch);
			pch = strtok (NULL, " ");

			spinners.push_back(new Spinner(Point3(x1/10.,y1/10.,0), .5, 10));
		}
		else if (line[0] == 'w')
		{
			//// step through line string and get the point info
			string tmp = line.substr(1,line.length()-1);
			char * pch = strtok ((char*)tmp.c_str()," ");

			x1 = atof(pch);
			pch = strtok (NULL, " ");

			y1 = atof(pch);
			pch = strtok (NULL, " ");

			switch (wallPoint)
			{
			case 0:
				p1 = Point3(x1/10.0,y1/10.0,0);
				wallPoint++;
				break;
			case 1:
				p2 = Point3(x1/10.0,y1/10.0,0);
				wallPoint++;
				break;
			case 2:
				p3 = Point3(x1/10.0,y1/10.0,0);
				wallPoint++;
				break;
			case 3:
				p4 = Point3(x1/10.0,y1/10.0,0);
				wallPoint = 0;
				createWall(p1,p2,p3,p4);
				break;
			}

		}
	}
	file.close();
}

void Table::Update()
{
	for (int i = 0; i<balls.size();i++)
	{
		if (balls[i]->toDelete)
		{
			balls.erase(balls.begin()+i);
			i = 0;
		}
	}
	for (int i = 0; i<balls.size();i++)
	{
		balls[i]->Update();
	}

	for (int i = 0;i<spinners.size();i++)
	{
		spinners[i]->Update();
	}
	
	// the quad tree needs to be rebuilt every frame. Add the moving parts to the tree and let it build
	vector<GameObject*> tmp = vector<GameObject*>(balls.begin(), balls.end());
	tree.AddMovingObjects(tmp);
	// check for collision
	tree.CheckCollisions();
	//tree.BruteCollisions(pins, balls);
}

void Table::Draw()
{
	// draw the backboard
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_QUADS);
	glVertex3f(-8,16,0);     glTexCoord2f (0, 0);
	glVertex3f(-8, 0,0);     glTexCoord2f (1, 0);
	glVertex3f (8, 0, 0);    glTexCoord2f (1, 1);
	glVertex3f (8,16,0);     glTexCoord2f (0, 1);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 2);

	// draw the tree for debug purposes
	tree.Draw();

	// draw the pins
	for (int i = 0;i<pins.size();i++)
	{
		pins[i]->Draw();
	}

	for (int i = 0;i<spinners.size();i++)
	{
		spinners[i]->Draw();
	}

	// draw the balls
	for (int i = 0;i<balls.size();i++)
	{
		balls[i]->Draw();
	}

	for (int i = 0;i<holes.size();i++)
	{
		holes[i]->Draw();
	}

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i<tableWallPoints.size()-1;i++)
	{
		glVertex3f(tableWallPoints[i]->x, tableWallPoints[i]->y, 0);
		/*Plane plane = Plane(*tableWallPoints[i],*tableWallPoints[i+1],Point3((*tableWallPoints[i]).x,(*tableWallPoints[i]).y,-1));
		glVertex3f(tableWallPoints[i]->x + plane.normal.x, tableWallPoints[i]->y + plane.normal.y, 0);*/
	}
	glEnd();
}

void Table::createWall( Point3 p0, Point3 p1, Point3 p2, Point3 p3 )
{
	float t = 0, step = 1.0/STEPS;
	Point3 p[STEPS];
	tableWallPoints.push_back(new Point3(p0));

	// (1-t)^3 * p0 + 3t(1-t)^2*p1 + 3t^2(1-t)p2+t^3*p3
	for (int i = 0; i< STEPS;i++)
	{
		p[i] = Point3(p0*pow((1.0f-t),3.0f) + p1*3*t*pow((1.0f-t),2.0f) + p2*3*pow(t,2.0f)*(1.0-t) + p3*pow(t,3.0f));

		Vector3 v = p[i]-*tableWallPoints.back();
		float l = v.getLength();
		if (l >= .2)
		{
			tableWallPoints.push_back(new Point3(p[i]));
		}
		t+=step;
	}
	tableWallPoints.push_back(new Point3(p3));
}

void Table::spawnBall()
{
	Ball *newBall = new Ball(Point3(-4,16,0),fG, .5);
	//newBall->Velocity(Vector3(-.2,.01,0));
	balls.push_back(newBall);
}