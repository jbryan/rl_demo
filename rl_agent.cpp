
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

#include "discrete.h"
#include "rl_agent.h"

RLAgent::RLAgent(Maze * maze) :
	maze_(*maze),
	time_step_(0),
	q_values_(
			boost::extents[maze_.get_width()][maze_.get_height()][Maze::NUM_ACT]
			)

{
	reset_value();
}

void RLAgent::reset_value()
{
	for (value_t::size_type x = 0; x < q_values_.shape()[0]; x++)
		for (value_t::size_type y = 0; y < q_values_.shape()[1]; y++)
			for (value_t::size_type a = 0; a < q_values_.shape()[2]; a++)
				q_values_[x][y][a] = 0.0;
}

void RLAgent::draw_policy() const
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

float& RLAgent::q( Maze::location_t const & s, Maze::action_t a)
{
	return q_values_[s[0]][s[1]][a];
}

float const& RLAgent::q( Maze::location_t const & s, Maze::action_t a) const
{
	return q_values_[s[0]][s[1]][a];
}

float RLAgent::max_over_actions( Maze::location_t const & s) const
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

Maze::action_t RLAgent::argmax_over_actions( Maze::location_t const & s) const
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

Maze::action_t RLAgent::choose_action( Maze::location_t const & s)
{
	time_step_++;
	double k = sqrt(time_step_);

	std::vector<double> probs;
	for (Maze::action_t a = Maze::MIN_ACT;  a < Maze::NUM_ACT; a = Maze::action_t(a+1))
	{
		probs.push_back(pow(k,q(s,a)));
		//std::cout << pow(k,q(s,a)) << std::endl;
	}

	DiscreteVariate logit(probs);
	return Maze::action_t(logit());

}

