#include <stdlib.h>
#include <GL/glut.h>
#include <string>

#include "include/AL/alut.h"
#include "Table.h"

using namespace std;


#define FPS 1

Table *table;

// Lighting values
GLfloat  whiteLight[] = { 1.f, 1.f, 1.f, 1.0f };
GLfloat  sourceLight[] = { 1.f, 1.f, 1.f, 1.0f };
GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 0.0f };

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	// position the camera far enough away so that a board of 16X16 will fill the entire screen
	//glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

	glTranslatef(0,-8,-9);
	//glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(3);
	table->Draw();
	//glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	//glutWireSphere(1,100,100);
	glPopMatrix();
	//glFlush();

	glutSwapBuffers();
}

void reshape (int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//// Setup and enable light 0
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
	//glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
	//glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

}

void animation(void)
{
	table->Update();
	glutPostRedisplay();
}

// Called each "frame" to update the game's components
void GameTimer(int frame)
{
	glutTimerFunc(frame, GameTimer, frame);
	animation();
}

void playFile (const char *wavName)
{
	ALuint buffer;
	ALuint source;
	ALenum error;
	ALint status;

	/* Create an AL buffer from the given sound file. */
	buffer = alutCreateBufferFromFile (wavName);
	if (buffer == AL_NONE)
	{
		error = alutGetError ();
		fprintf (stderr, "Error loading file: '%s'\n",
			alutGetErrorString (error));
		alutExit ();
		exit (EXIT_FAILURE);
	}

	/* Generate a single source, attach the buffer to it and start playing. */
	alGenSources (1, &source);
	alSourcei (source, AL_BUFFER, buffer);
	alSourcePlay (source);

	/* Normally nothing should go wrong above, but one never knows... */
	error = alGetError ();
	if (error != ALUT_ERROR_NO_ERROR)
	{
		fprintf (stderr, "%s\n", alGetString (error));
		alutExit ();
		exit (EXIT_FAILURE);
	}
}

void init(void) 
{
	table = new Table();
	table->thisTable = table;
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	alutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init();
	GameTimer(FPS);
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutSpecialFunc(Table::keyboardS);
	glutKeyboardFunc(Table::keyboardN);

	glutMainLoop();
	
	if (!alutExit ())
	{
		ALenum error = alutGetError ();
		fprintf (stderr, "%s\n", alutGetErrorString (error));
		exit (EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}