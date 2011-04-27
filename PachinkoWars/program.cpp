#include <stdlib.h>
#include <GL/glut.h>
#include <string>

#include "include/AL/alut.h"
#include "Table.h"

using namespace std;


#define FPS 1000/30

Table table;

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	// position the camera far enough away so that a board of 16X16 will fill the entire screen
	glTranslatef(0,-8,-9);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(3);
	table.Draw();
	
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
	table = Table();

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}


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
	glutInit(&argc, argv);
	alutInit(&argc, argv);
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
	
	if (!alutExit ())
	{
		ALenum error = alutGetError ();
		fprintf (stderr, "%s\n", alutGetErrorString (error));
		exit (EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}