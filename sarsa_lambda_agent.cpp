
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include "sarsa_lambda_agent.h"
#include "discrete.h"

SarsaLambdaAgent::SarsaLambdaAgent(Maze * maze) :
	RLAgent(maze),
	e_values_(
			boost::extents[maze_.get_width()][maze_.get_height()][Maze::NUM_ACT]
			),
	gamma_(0.9),
	lambda_(0.9)
{ 
	new_act = choose_action(maze_.get_location());
}

SarsaLambdaAgent::SarsaLambdaAgent(Maze * maze, float gamma, float lambda) :
	RLAgent(maze),
	e_values_(
			boost::extents[maze_.get_width()][maze_.get_height()][Maze::NUM_ACT]
			),
	gamma_(gamma),
	lambda_(lambda)
{ 
	new_act = choose_action(maze_.get_location());
}


/*
 * Perform an action in the maze and learn from it
 */
void SarsaLambdaAgent::act()
{

	//get s
	Maze::location_t current_loc = maze_.get_location();

	//a becomes the old a'
	Maze::action_t current_act = new_act;

	//do the action and get the reward
	float reward = maze_.perform_action(current_act);

	//get new location s'
	Maze::location_t new_loc = maze_.get_location();

	//choose a new action for future a'
	new_act = choose_action(new_loc);

	double delta = reward + 
			gamma_ * q(new_loc,new_act) - 
			q(current_loc,current_act);

	Maze::location_t s;
	//update e value for previous state
	for (s[0] = 0; s[0] < e_values_.shape()[0]; s[0]++)
	{
		for (s[1] = 0; s[1] < e_values_.shape()[1]; s[1]++)
		{
			for (Maze::action_t a = Maze::MIN_ACT;  a < Maze::NUM_ACT; 
					a = Maze::action_t(a+1)) 
			{
				e(s,a) *= gamma_ * lambda_;
			}
		}
	}
	e(current_loc, current_act) += 1;

	//update q value for previous state
	for (s[0] = 0; s[0] < q_values_.shape()[0]; s[0]++)
	{
		for (s[1] = 0; s[1] < q_values_.shape()[1]; s[1]++)
		{
			for (Maze::action_t a = Maze::MIN_ACT;  a < Maze::NUM_ACT; 
					a = Maze::action_t(a+1)) 
			{
				q(s,a) += alpha(s,a) * delta * e(s,a);
			}
		}
	}

}

/*
 * Convenience function for accessing eligibility traces
 */
float& SarsaLambdaAgent::e( Maze::location_t const & s, Maze::action_t a)
{
	return e_values_[s[0]][s[1]][a];
}

/*
 * Convenience function for accessing eligibility traces
 */
float const& SarsaLambdaAgent::e( Maze::location_t const & s, Maze::action_t a) const
{
	std::cout << s[0] << std::endl;
	return e_values_[s[0]][s[1]][a];
}
