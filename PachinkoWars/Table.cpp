#include "Table.h"

float xs[1000], ys[1000];
Point3 tableWallPoints[1000];
int xp = 0, yp = 0;

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
	fG = new Vector3(0,-.01,0);

	// set up the pin and ball vectors
	pins = vector<Pin*>();
	balls = vector<Ball*>();
	balls.push_back(new Ball(Point3(0,8,0), fG));

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
	tree.BuildStaticTree(objects, new Point3(-8, 0, 0), 16.0, 16.0);
}

void Table::FileIn()
{
	string line;
	fstream file;
	int *step = new int(0);

	file.open(fileName);
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
				p1 = Point3(x1,y1,0);
				wallPoint++;
				break;
			case 1:
				p2 = Point3(x1,y1,0);
				wallPoint++;
				break;
			case 2:
				p3 = Point3(x1,y1,0);
				wallPoint++;
				break;
			case 3:
				p4 = Point3(x1,y1,0);
				CreateSides(p1, p2, p3, p4, step);
				wallPoint = 0;
				break;

			}

		}
	}
	file.close();
}

void Table::CreateSides( Point3 p1, Point3 p2, Point3 p3, Point3 p4, int* step )
{
	double a[5];
	double b[5];
	a[0] = (-p1.x + 3 * p2.x - 3 * p3.x + p4.x) / 6.0f;
	a[1] = (3 * p1.x - 6 * p2.x + 3 * p3.x) / 6.0f;
	a[2] = (-3 * p1.x + 3 * p3.x) / 6.0f;
	a[3] = (p1.x + 4 * p2.x + p3.x) / 6.0f;
	b[0] = (-p1.y + 3 * p2.y - 3 * p3.y + p4.y) / 6.0f;
	b[1] = (3 * p1.y - 6 * p2.y + 3 * p3.y) / 6.0f;
	b[2] = (-3 * p1.y + 3 * p3.y) / 6.0f;
	b[3] = (p1.y + 4 * p2.y + p3.y) / 6.0f;

	tableWallPoints[*step] = Point3(a[3], b[3], 0);

	for(int i = 1; i <= 3; i++){
		double j = (double)i / (double)3;
		tableWallPoints[*step] = Point3(pow(j,3.0)*a[0] + pow(j,2.0)*a[1] + j*a[2] + a[3],pow(j,3.0)*b[0] + pow(j,2.0)*b[1] + j*b[2] + b[3],0);
		*step += 1;
	}
}

void Table::Update()
{
	for (int i = 0; i<balls.size();i++)
	{
		balls[i]->Update();
	}
	
	// the quad tree needs to be rebuilt every frame. Add the moving parts to the tree and let it build
	vector<GameObject*> tmp = vector<GameObject*>(balls.begin(), balls.end());
	tree.AddMovingObjects(tmp);
	// check for collision
	tree.CheckCollisions();
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

	// draw the balls
	for (int i = 0;i<balls.size();i++)
	{
		balls[i]->Draw();
	}

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i<10;i++)
	{
		glVertex3f(tableWallPoints[i].x/10., tableWallPoints[i].y/10., 0);
	}
	glEnd();
	
}