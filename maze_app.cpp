
#include <string>
#include <stdexcept>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>
#include <sys/time.h>

#include "maze_app.h"

MazeApp::MazeApp() :
	my_maze(10,10), agent(&my_maze)
{ 
	//my_maze.set_schocastic_actions_(true);
}

MazeApp::~MazeApp()
{ }

void MazeApp::draw_scene()
{
	timeval current_time;
	gettimeofday(&current_time, NULL);
	static timeval last_act_time = current_time;

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
	if (current_time.tv_sec > last_act_time.tv_sec || 
			current_time.tv_usec - last_act_time.tv_usec > 50000)
	{
		agent.act();
		last_act_time = current_time;
	}

	//draw the maze
	agent.draw_policy();
	my_maze.draw_maze();

	glPopMatrix();
	

	/* Draw it to the screen */
	SDL_GL_SwapBuffers( );
}
