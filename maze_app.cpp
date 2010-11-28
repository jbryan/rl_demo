
#include <string>
#include <stdexcept>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>
#include <ctime>

#include "maze_app.h"

MazeApp::MazeApp() :
	my_maze(10,10), agent(&my_maze)
{ }

MazeApp::~MazeApp()
{ }

void MazeApp::draw_scene()
{
	static clock_t last_act_time = clock();

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

	//do an action if "enough" time has passed
	if (clock() - last_act_time > 50000)
	{
		agent.act();
		last_act_time = clock();
	}

	//draw the maze
	agent.draw_policy();
	my_maze.draw_maze();

	glPopMatrix();
	

	/* Draw it to the screen */
	SDL_GL_SwapBuffers( );
}
