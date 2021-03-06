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


#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "maze.h"
#include "discrete.h"

Maze::Maze(int x, int y) :
	grid(boost::extents[x][y]), 
	location(), 
	stochastic_actions_(false)
{
	std::vector<double> probs(x*y,1.0);

	//ensure start position is neither goal
	//nor hazard
	probs[0] = 0;

	//create goals
	for (int i = 0; i < 2; i++)
	{
		DiscreteVariate goal(probs);
		std::size_t g = goal();
		grid.origin()[g] = 5.0f;
		probs[g] = 0;
	}

	//create hazards
	for (int i = 0; i < 3*sqrt(x*y); i++)
	{
		DiscreteVariate traps(probs);
		std::size_t t = traps();
		grid.origin()[t] = -1.0f;
		probs[t] = 0;
	}

	location[0] = 0;
	location[1] = 0;
}

/*
 * Draw the maze as a colored grid.
 */
void Maze::draw_maze() const
{
	grid_t::size_type x,y;
	GLfloat x_scale = 1.0 / grid.shape()[0];
	GLfloat y_scale = 1.0 / grid.shape()[1];

	//draw the grid
	glLineWidth(3.0);
	for (x = 0; x < grid.shape()[0]; x++)
	{
		for (y = 0; y < grid.shape()[1]; y++)
		{
			GLfloat red, blue, green;
			if (x == 0 && y == 0)
			{
				//color home differently
				red = 0; green = 0; blue = 1;
			}
			else
			{
				red = (grid[x][y] > 0) ? 1.0 - fabs(grid[x][y]) : 1.0f;
				green  = (grid[x][y] < 0) ? 1.0 - fabs(grid[x][y]) : 1.0f;
				blue = 1.0 - fabs(grid[x][y]);
			}
			glColor3f(red, green, blue);


			glBegin( GL_LINE_LOOP );
				glVertex3f( x * x_scale, y * y_scale, 0.0);
				glVertex3f( (x+0.9) * x_scale, y * y_scale, 0.0);
				glVertex3f( (x+0.9) * x_scale, (y+0.9) * y_scale, 0.0);
				glVertex3f( x * x_scale, (y+0.9) * y_scale, 0.0);
			glEnd();
		}
	}

	//draw current location
	glColor3f( 0.0, 0.0, 1.0);
	x = location[0];
	y = location[1];
	glBegin( GL_POLYGON ); //base
		glVertex3f( (x + 0.2) * x_scale, (y + 0.2) * y_scale, x_scale * 0.2);
		glVertex3f( (x + 0.2) * x_scale, (y + 0.7) * y_scale, x_scale * 0.2);
		glVertex3f( (x + 0.7) * x_scale, (y + 0.7) * y_scale, x_scale * 0.2);
		glVertex3f( (x + 0.7) * x_scale, (y + 0.2) * y_scale, x_scale * 0.2);
	glEnd();
	glBegin( GL_POLYGON ); //side
		glVertex3f( (x + 0.45) * x_scale, (y + 0.45) * y_scale, x_scale * 0.65);
		glVertex3f( (x + 0.2) * x_scale, (y + 0.2) * y_scale, x_scale * 0.2);
		glVertex3f( (x + 0.2) * x_scale, (y + 0.7) * y_scale, x_scale * 0.2);
	glEnd();
	glBegin( GL_POLYGON ); //side
		glVertex3f( (x + 0.45) * x_scale, (y + 0.45) * y_scale, x_scale * 0.65);
		glVertex3f( (x + 0.2) * x_scale, (y + 0.7) * y_scale, x_scale * 0.2);
		glVertex3f( (x + 0.7) * x_scale, (y + 0.7) * y_scale, x_scale * 0.2);
	glEnd();
	glBegin( GL_POLYGON ); //side
		glVertex3f( (x + 0.45) * x_scale, (y + 0.45) * y_scale, x_scale * 0.65);
		glVertex3f( (x + 0.7) * x_scale, (y + 0.7) * y_scale, x_scale * 0.2);
		glVertex3f( (x + 0.7) * x_scale, (y + 0.2) * y_scale, x_scale * 0.2);
	glEnd();
	glBegin( GL_POLYGON ); //side
		glVertex3f( (x + 0.45) * x_scale, (y + 0.45) * y_scale, x_scale * 0.65);
		glVertex3f( (x + 0.2) * x_scale, (y + 0.2) * y_scale, x_scale * 0.2);
		glVertex3f( (x + 0.7) * x_scale, (y + 0.2) * y_scale, x_scale * 0.2);
	glEnd();
	
}

/*
 * update the position of the agent based on the action it performs
 */
float Maze::perform_action(action_t action)
{
	//if the environment is stochastic
	if (stochastic_actions_)
	{
		//randomly select "real" action
		std::vector<double> probs;
		for (Maze::action_t a = Maze::MIN_ACT;  a < Maze::NUM_ACT; 
				a = Maze::action_t(a+1))
		{
			//choose requested action with probability .7 and another 
			//action with probability .1
			probs.push_back(a == action ? 7 : 1);
		}
		DiscreteVariate rand_action(probs);
		action = action_t(rand_action());
	}
	
	//get the updated location
	location = transition(location, action);
	float value = grid(location); 

	//if this was a target, jump to initial position
	if (value > 0)
	{
		location[0] = 0;
		location[1] = 0;
	}
	//return reward in state - 1 cost for action
	return value - 0.005;
}

/*
 * Give a new location by computing the effect of the action on the
 * old location
 */
Maze::location_t Maze::transition(location_t loc, action_t action)
{
	switch (action)
	{
		case UP:
			if (loc[1] < grid.shape()[1]-1)
				loc[1]++;
			break;
		case DOWN:
			if (loc[1] > 0)
				loc[1]--;
			break;
		case RIGHT:
			if (loc[0] < grid.shape()[0]-1)
				loc[0]++;
			break;
		case LEFT:
			if (loc[0] > 0)
				loc[0]--;
			break;
	}

	return loc;
}

/*
 * get the width of the maze
 */
unsigned int Maze::get_width() const
{
	return grid.shape()[0];
}

/*
 * get the height of the maze
 */
unsigned int Maze::get_height() const
{
	return grid.shape()[1];
}

/*
 * set whether to update state stochastically or no
 */
void Maze::set_stochastic_actions( bool stochastic ) 
{
	stochastic_actions_ = stochastic;
}
