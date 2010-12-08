
#include <vector>
#include <algorithm>
#include <limits>
#include "sarsa_lambda_agent.h"
#include "discrete.h"

SarsaLambdaAgent::SarsaLambdaAgent(Maze * maze) :
	RLAgent(maze),
	gamma_(0.9),
	lambda_(0.9),
	alpha_(1)
{ }

SarsaLambdaAgent::SarsaLambdaAgent(Maze * maze, float gamma, float lambda) :
	RLAgent(maze),
	gamma_(gamma),
	lambda_(lambda),
	alpha_(1)
{ }


void SarsaLambdaAgent::act()
{

	Maze::location_t current_loc = maze_.get_location();
	//Choose the action

	//std::vector<double> probs(4,1.0);
	//DiscreteVariate choose(probs);
	//Maze::action_t action = (Maze::action_t) choose();
	Maze::action_t action = choose_action(current_loc);;

	//do the action and get the reward
	float reward = maze_.perform_action(action);

	//get new location
	Maze::location_t new_loc = maze_.get_location();


	//update q value for previous state
	q(current_loc,action) += alpha(current_loc,action) * (
			reward + 
			gamma_ * max_over_actions(new_loc) - 
			q(current_loc,action)
			);
}
