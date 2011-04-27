#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <vector>

// basic file operations
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


#define FPS 1000/30
#define fileName "PACHINKO.txt"

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	// position the camera far enough away so that a board of 16X16 will fill the entire screen
	glTranslatef(0,-8,-9);
	glColor3f(1.0, 1.0, 1.0);


	
	glPopMatrix();
	glutSwapBuffers();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void animation(void)
{
	// get the force from spring, calculate force of gravity on bar, imply the forces on the bar, calculate new positions of bar and spring
	glutPostRedisplay();
}

void FileIn() 
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

		// step through line string and get the point info
		char * pch = strtok ((char*)line.c_str()," ");

		x1 = atof(pch);
		pch = strtok (NULL, " ");

		y1 = atof(pch);
		pch = strtok (NULL, " ");

		x2 = atof(pch);
		pch = strtok (NULL, " ");

		y2 = atof(pch);
	}
	file.close();
}

// Called each "frame" to update the game's components
void GameTimer(int frame)
{
	// read in the file
	FileIn();
	glutTimerFunc(frame, GameTimer, frame);
	animation();
}

void init(void) 
{

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}

//http://www.flipcode.com/archives/OpenGL_Camera.shtml
void keyboardS (int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_RIGHT:
		break;
	case GLUT_KEY_LEFT:
		break;
	default:
		break;
	}
}

void keyboardN(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'Q':
	case 'q':
		exit(0);
		break;
	case 'r':
	case 'R':
		init();
	}
}

int main(int argc, char** argv)
{
	srand((unsigned)time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init();
	GameTimer(FPS);
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboardS);
	glutKeyboardFunc(keyboardN);
	glutMainLoop();
	return 0;
}