
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <algorithm>
#include <limits>
#include "q_agent.h"
#include "discrete.h"

QAgent::QAgent(Maze * maze) :
	maze_(*maze), 
	gamma_(0.95),
	alpha_(0.5),
	q_values_(
			boost::extents[maze_.get_width()][maze_.get_height()][Maze::NUM_ACT]
			)
{
	reset_value();
}

QAgent::QAgent(Maze * maze, float gamma) :
	maze_(*maze), 
	gamma_(gamma),
	alpha_(0.5),
	q_values_(
			boost::extents[maze_.get_width()][maze_.get_height()][Maze::NUM_ACT]
			)
{
	reset_value();
}

void QAgent::reset_value()
{
	for (value_t::size_type x = 0; x < q_values_.shape()[0]; x++)
		for (value_t::size_type y = 0; y < q_values_.shape()[1]; y++)
			for (value_t::size_type a = 0; a < q_values_.shape()[2]; a++)
				q_values_[x][y][a] = 0.0;
}

void QAgent::act()
{

	Maze::location_t current_loc = maze_.get_location();
	//Choose the action

	//std::vector<double> probs(4,1.0);
	//DiscreteVariate choose(probs);
	//Maze::action_t action = (Maze::action_t) choose();
	Maze::action_t action = argmax_over_actions(current_loc);;

	//do the action and get the reward
	float reward = maze_.perform_action(action);

	//get new location
	Maze::location_t new_loc = maze_.get_location();

	//update q value for previous state
	q(current_loc,action) += alpha_ * (
			reward + 
			gamma_ * max_over_actions(new_loc) - 
			q(current_loc,action)
			);
}

void QAgent::draw_policy() const
{
	value_t::size_type x,y;
	GLfloat x_scale = 1.0 / q_values_.shape()[0];
	GLfloat y_scale = 1.0 / q_values_.shape()[1];
	
	//draw the grid
	Maze::location_t loc;
	for (loc[0] = 0; loc[0] < q_values_.shape()[0]; loc[0]++)
	{
		for (loc[1] = 0; loc[1] < q_values_.shape()[1]; loc[1]++)
		{
			for (Maze::action_t a = Maze::MIN_ACT;  a < Maze::NUM_ACT; a = Maze::action_t(a+1))
			{
				float loc_value = q(loc,a);
				GLfloat red, blue, green;
				red = (loc_value < 0) ? fabs(loc_value) : 0.0f;
				green  = (loc_value > 0) ? fabs(loc_value) : 0.0f;
				glColor3f(red, green, 0.0);

				glPushMatrix();
				glTranslatef((loc[0]+0.45) * x_scale, (loc[1]+0.45) * y_scale, 0.0);
				glRotatef( a * 90, 0, 0, 1.0);

				glBegin( GL_POLYGON );
					glVertex3f( -x_scale /4.5, y_scale / 5.0, 0.0);
					glVertex3f( x_scale /4.5, y_scale / 5.0, 0.0);
					glVertex3f( 0, y_scale / 2.5, 0.0);
				glEnd();

				glPopMatrix();
			}
		}
	}

}

float& QAgent::q( Maze::location_t const & s, Maze::action_t a)
{
	return q_values_[s[0]][s[1]][a];
}

float const& QAgent::q( Maze::location_t const & s, Maze::action_t a) const
{
	return q_values_[s[0]][s[1]][a];
}

float QAgent::max_over_actions( Maze::location_t const & s) const
{
	Maze::action_t action;
	float max_value = -std::numeric_limits<float>::max();
	for (Maze::action_t a = Maze::MIN_ACT;  a < Maze::NUM_ACT; a = Maze::action_t(a+1))
	{
		if (q(s,a) > max_value)
		{
			action = a;
			max_value = q(s,a);
		}
	}
	return max_value;
}

Maze::action_t QAgent::argmax_over_actions( Maze::location_t const & s) const
{
	Maze::action_t action;
	float max_value = -std::numeric_limits<float>::max();
	for (Maze::action_t a = Maze::MIN_ACT;  a < Maze::NUM_ACT; a = Maze::action_t(a+1))
	{
		if (q(s,a) > max_value)
		{
			action = a;
			max_value = q(s,a);
		}
	}
	return action;
}


