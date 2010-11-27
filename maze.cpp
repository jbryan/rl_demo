
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <cmath>
#include "maze.h"

Maze::Maze(int x, int y) :
	maze(boost::extents[x][y])
{
	maze[0][0] = -1.0;
	maze[1][0] = 1.0;
}

void Maze::draw_maze()
{
	maze_t::size_type x,y;
	GLfloat x_scale = 1.0 / maze.shape()[0];
	GLfloat y_scale = 1.0 / maze.shape()[1];
	for (x = 0; x < maze.shape()[0]; x++)
	{
		for (y = 0; y < maze.shape()[1]; y++)
		{
			GLfloat red, blue, green;
			red = (maze[x][y] > 0) ? 1.0 - abs(maze[x][y]) : 1.0f;
			green  = (maze[x][y] < 0) ? 1.0 - abs(maze[x][y]) : 1.0f;
			blue = 1.0 - abs(maze[x][y]);
			glColor3f(red, green, blue);

			glBegin( GL_QUADS );
				glVertex3f( x * x_scale, y * y_scale, 0.0);
				glVertex3f( (x+0.9) * x_scale, y * y_scale, 0.0);
				glVertex3f( (x+0.9) * x_scale, (y+0.9) * y_scale, 0.0);
				glVertex3f( x * x_scale, (y+0.9) * y_scale, 0.0);
			glEnd();
		}
	}
}

float Maze::perform_action(action_t action)
{
	switch (action)
	{
		case UP:
			if (location[1] < maze.shape()[1])
				location[1]++;
			break;
		case DOWN:
			if (location[1] < maze.shape()[1])
				location[1]--;
			break;
		case RIGHT:
			if (location[0] < maze.shape()[0])
				location[0]++;
			break;
		case LEFT:
			if (location[0] < maze.shape()[0])
				location[1]--;
			break;
	}

	return maze(location);
}
