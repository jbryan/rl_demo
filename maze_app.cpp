/*
 *	Author: Josh Bryan <josh.bryan@gmail.com>
 *	This file is copyright 2010 by Josh Bryan.
 *
 *  This file is part of Reinforcement Learning Demo.
 *
 *  Foobar is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any later
 *  version.
 *
 *  Foobar is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <string>
#include <stdexcept>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>

#include <cmath>
#include <sys/time.h>

#include "maze_app.h"

MazeApp::MazeApp() :
	q_maze(10,10), sarsa_maze(q_maze), q_agent(&q_maze), sarsa_agent(&sarsa_maze)
{ 
	//my_maze.set_schocastic_actions_(true);
}

MazeApp::~MazeApp()
{ }

/*
 * Draw the scene and update the two learning agents.
 */
void MazeApp::draw_scene()
{
	timeval current_time;
	gettimeofday(&current_time, NULL);
	static timeval last_act_time = current_time;

	/* Clear The Screen And The Depth Buffer */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	//update model
	theta = fmod(2 * (current_time.tv_sec + current_time.tv_usec * 1e-6), 360.0 );

	//do an action if "enough" time has passed
	if (current_time.tv_sec > last_act_time.tv_sec || 
			current_time.tv_usec - last_act_time.tv_usec > 50000)
	{
		q_agent.act();
		sarsa_agent.act();
		last_act_time = current_time;
	}

	glPushMatrix();
		glTranslatef( -0.7, 0, -2.5);
		glRotatef(-45, 1.0, 0.0, 0.0);
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef( -0.5, -0.5, 0);

		//draw the q maze
		q_agent.draw_policy();
		q_maze.draw_maze();

		//glutStrokeCharacter(GLUT_STROKE_ROMAN, 'Q');
	glPopMatrix();

	glPushMatrix();
		glTranslatef( 0.7, 0, -2.5);
		glRotatef(-45, 1.0, 0.0, 0.0);
		glRotatef(theta, 0.0, 0.0, 1.0);
		glTranslatef( -0.5, -0.5, 0);

		//draw the sarsa maze
		sarsa_agent.draw_policy();
		sarsa_maze.draw_maze();
	glPopMatrix();

	

	/* Draw it to the screen */
	SDL_GL_SwapBuffers( );
}
