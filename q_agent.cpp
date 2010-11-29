
#include <vector>
#include <algorithm>
#include <limits>
#include "q_agent.h"
#include "discrete.h"

QAgent::QAgent(Maze * maze) :
	RLAgent(maze),
	gamma_(0.95),
	alpha_(0.5)
{ }

QAgent::QAgent(Maze * maze, float gamma) :
	RLAgent(maze),
	gamma_(gamma),
	alpha_(0.5)
{ }


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
