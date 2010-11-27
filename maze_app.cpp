
#include <string>
#include <stdexcept>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>
#include "maze_app.h"

MazeApp::MazeApp()
{ }

MazeApp::~MazeApp()
{ }

void MazeApp::draw_scene()
{
	/* Clear The Screen And The Depth Buffer */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	//update model
	theta += 0.9f;

	glPushMatrix();
	glTranslatef( 0, 0, -5);
	glRotatef(theta, 0.0, 1.0, 0.0);

	glColor3f( 1.0f, 1.0f, 1.0f);
	glBegin( GL_LINE_LOOP );
		for (float t = 0; t <= 2 * M_PI; t += 0.1)
		{
			glVertex3f( sin(t), cos(t), 0);
		}
	glEnd();

	glPopMatrix();

	/* Draw it to the screen */
	SDL_GL_SwapBuffers( );
}
