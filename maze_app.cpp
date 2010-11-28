
#include <string>
#include <stdexcept>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>
#include "maze_app.h"

MazeApp::MazeApp() :
	my_maze(5,5), agent(&my_maze)
{ }

MazeApp::~MazeApp()
{ }

void MazeApp::draw_scene()
{
	/* Clear The Screen And The Depth Buffer */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	//update model
	theta += 0.2f;

	glPushMatrix();
	glTranslatef( 0, 0, -2);
	glRotatef(-45, 1.0, 0.0, 0.0);
	glRotatef(theta, 0.0, 0.0, 1.0);
	glTranslatef( -0.5, -0.5, 0);

	agent.act();
	my_maze.draw_maze();

	glPopMatrix();
	

	/* Draw it to the screen */
	SDL_GL_SwapBuffers( );
}
