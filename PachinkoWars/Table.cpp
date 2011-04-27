#include "Table.h"

int xs[1000], ys[1000], xp = 0, yp = 0;

Table::Table(void)
{
	init();
}


Table::~Table(void)
{
}

void Table::init()
{
	int width, height;
	int nComponents;
	void* pTextureImage;

	//glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Create texture for cube; load marble texture from file and bind it

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
	float x1, y1,vx1,vy1, x2, y2, vx2, vy2;

	for(int i = 0; !file.eof(); i ++){

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
		xs[xp++] = x1-2;
		xs[xp++] = x2-2;
		ys[yp++] = y1;
		ys[yp++] = y2;
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
			xs[xp++] = x1-2;
			xs[xp++] = x2-2;
			ys[yp++] = y1;
			ys[yp++] = y2;
		}
	}
	file.close();
}

void Table::Draw()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_QUADS);
	glVertex3f(-8,16,0);     glTexCoord2f (0, 0);
	glVertex3f(-8, 0,0);     glTexCoord2f (1, 0);
	glVertex3f (8, 0, 0);    glTexCoord2f (1, 1);
	glVertex3f (8,16,0);     glTexCoord2f (0, 1);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 1);
	glColor3f(1,1,1);
	for (int i = 0; i < xp; i+=2)
	{
		glBegin(GL_LINE_LOOP);
		glVertex3f(-xs[i]/10.f, ys[i]/10.f, 1);
		glVertex3f(-xs[i+1]/10.f, ys[i+1]/10.f, 1);
		glEnd();
	}
}