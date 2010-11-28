
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "maze.h"
#include "discrete.h"

Maze::Maze(int x, int y) :
	grid(boost::extents[x][y]), location()
{
	std::vector<double> probs(x*y,1.0);

	DiscreteVariate goal(probs);
	std::size_t g = goal();
	grid.origin()[g] = 1.0f;
	probs[g] = 0;

	for (int i = 0; i < sqrt(x*y); i++)
	{
		DiscreteVariate traps(probs);
		std::size_t t = traps();
		grid.origin()[t] = -1.0f;
		probs[t] = 0;
	}

	location[0] = 0;
	location[1] = 0;
}

void Maze::draw_maze()
{
	grid_t::size_type x,y;
	GLfloat x_scale = 1.0 / grid.shape()[0];
	GLfloat y_scale = 1.0 / grid.shape()[1];
	
	//draw the grid
	for (x = 0; x < grid.shape()[0]; x++)
	{
		for (y = 0; y < grid.shape()[1]; y++)
		{
			GLfloat red, blue, green;
			red = (grid[x][y] > 0) ? 1.0 - fabs(grid[x][y]) : 1.0f;
			green  = (grid[x][y] < 0) ? 1.0 - fabs(grid[x][y]) : 1.0f;
			blue = 1.0 - fabs(grid[x][y]);
			glColor3f(red, green, blue);

			glBegin( GL_QUADS );
				glVertex3f( x * x_scale, y * y_scale, 0.0);
				glVertex3f( (x+0.9) * x_scale, y * y_scale, 0.0);
				glVertex3f( (x+0.9) * x_scale, (y+0.9) * y_scale, 0.0);
				glVertex3f( x * x_scale, (y+0.9) * y_scale, 0.0);
			glEnd();
		}
	}

	//draw current location
	glColor4f( 0.0, 0.0, 1.0, 0.3);
	x = location[0];
	y = location[1];
	glBegin( GL_POLYGON );
		glVertex3f( (x + 0.2) * x_scale, (y + 0.2) * y_scale, x_scale * 0.2);
		glVertex3f( (x + 0.2) * x_scale, (y + 0.7) * y_scale, x_scale * 0.2);
		glVertex3f( (x + 0.7) * x_scale, (y + 0.7) * y_scale, x_scale * 0.2);
		glVertex3f( (x + 0.7) * x_scale, (y + 0.2) * y_scale, x_scale * 0.2);
	glEnd();
	glBegin( GL_POLYGON );
		glVertex3f( (x + 0.45) * x_scale, (y + 0.45) * y_scale, x_scale * 0.65);
		glVertex3f( (x + 0.2) * x_scale, (y + 0.2) * y_scale, x_scale * 0.2);
		glVertex3f( (x + 0.2) * x_scale, (y + 0.7) * y_scale, x_scale * 0.2);
	glEnd();
	glBegin( GL_POLYGON );
		glVertex3f( (x + 0.45) * x_scale, (y + 0.45) * y_scale, x_scale * 0.65);
		glVertex3f( (x + 0.2) * x_scale, (y + 0.7) * y_scale, x_scale * 0.2);
		glVertex3f( (x + 0.7) * x_scale, (y + 0.7) * y_scale, x_scale * 0.2);
	glEnd();
	glBegin( GL_POLYGON );
		glVertex3f( (x + 0.45) * x_scale, (y + 0.45) * y_scale, x_scale * 0.65);
		glVertex3f( (x + 0.7) * x_scale, (y + 0.7) * y_scale, x_scale * 0.2);
		glVertex3f( (x + 0.7) * x_scale, (y + 0.2) * y_scale, x_scale * 0.2);
	glEnd();
	glBegin( GL_POLYGON );
		glVertex3f( (x + 0.45) * x_scale, (y + 0.45) * y_scale, x_scale * 0.65);
		glVertex3f( (x + 0.2) * x_scale, (y + 0.2) * y_scale, x_scale * 0.2);
		glVertex3f( (x + 0.7) * x_scale, (y + 0.2) * y_scale, x_scale * 0.2);
	glEnd();
	
}

float Maze::perform_action(action_t action)
{
	switch (action)
	{
		case UP:
			if (location[1] < grid.shape()[1]-1)
				location[1]++;
			break;
		case DOWN:
			if (location[1] > 0)
				location[1]--;
			break;
		case RIGHT:
			if (location[0] < grid.shape()[0]-1)
				location[0]++;
			break;
		case LEFT:
			if (location[0] > 0)
				location[0]--;
			break;
	}

	return grid(location);
}
