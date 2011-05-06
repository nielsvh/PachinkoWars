#include "Table.h"

float xs[1000], ys[1000];
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
	fG = new Vector3(0,-.01,0);

	pins = vector<Pin*>();
	balls = vector<Ball*>();
	balls.push_back(new Ball(Point3(0,8,0), fG));


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
	// read in the file
	FileIn();

	/*vector<Pin*> tmp = PinLineCurve::GetCurvePins(Point3(xs[0], ys[0],0), Point3(xs[1], ys[1],0), Point3(xs[2], ys[2],0), Point3(xs[3], ys[3],0));
	pins.insert(pins.end(),tmp.begin(), tmp.end());*/

	tree = QuadTree();

	objects = vector<GameObject*>(pins.begin(), pins.end());
	tree.BuildStaticTree(objects, new Point3(-8, 0, 0), 16.0, 16.0);
}

void Table::FileIn()
{
	string line;
	fstream file;

	file.open(fileName);
	//Tests to see if file was found
	if (!file)
	{
		cout << "Unable to open file\n";
		//exit(1); // File could not be found, no points, exit the program
	}

	// the x and y of the start and end of a line as well as the vectors for curves
	float x1,x2,x3,x4,y1,y2,y3,y4;
	vector<Pin*> tmpp;

	for(int i = 0; !file.eof(); i++){

		getline(file, line);

		if (line.length() == 0)
		{
			continue;
		}

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

			xs[xp++] = (x1)/10.;
			xs[xp++] = (x2)/10.;
			xs[xp++] = (x3)/10.;
			xs[xp++] = (x4)/10.;
			ys[yp++] = (y1)/10.;
			ys[yp++] = (y2)/10.;
			ys[yp++] = (y3)/10.;
			ys[yp++] = (y4)/10.;

			tmpp = PinLineCurve::GetCurvePins(Point3(x1/10., y1/10.,0), Point3(x2/10., y2/10.,0),Point3(x3/10., y3/10.,0),Point3(x4/10., y4/10.,0));
			pins.insert(pins.end(),tmpp.begin(), tmpp.end());
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
			xs[xp++] = x1/10.;
			xs[xp++] = x2/10.;
			ys[yp++] = y1/10.;
			ys[yp++] = y2/10.;

			tmpp = PinLineCurve::GetLinePins(Point3(x1/10.f, y1/10.f,0), Point3(x2/10.f, y2/10.f,0));
			pins.insert(pins.end(),tmpp.begin(), tmpp.end());
			tmpp = PinLineCurve::GetLinePins(Point3(-x1/10.f, y1/10.f,0), Point3(-x2/10.f, y2/10.f,0));
			pins.insert(pins.end(),tmpp.begin(), tmpp.end());
		}
	}
	file.close();
}

void Table::Update()
{
	for (int i = 0; i<balls.size();i++)
	{
		balls[i]->Update();
	}
	vector<GameObject*> tmp = vector<GameObject*>(balls.begin(), balls.end());

	tree.AddMovingObjects(tmp);
}

void Table::Draw()
{
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_QUADS);
	glVertex3f(-8,16,0);     glTexCoord2f (0, 0);
	glVertex3f(-8, 0,0);     glTexCoord2f (1, 0);
	glVertex3f (8, 0, 0);    glTexCoord2f (1, 1);
	glVertex3f (8,16,0);     glTexCoord2f (0, 1);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 2);

	tree.Draw();

	for (int i = 0;i<pins.size();i++)
	{
		pins[i]->Draw();
	}

	for (int i = 0;i<balls.size();i++)
	{
		balls[i]->Draw();
	}
	
}