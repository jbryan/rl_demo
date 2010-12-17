
#include <vector>
#include <algorithm>
#include <limits>
#include "q_agent.h"
#include "discrete.h"

QAgent::QAgent(Maze * maze) :
	RLAgent(maze),
	gamma_(0.9)
{ }

QAgent::QAgent(Maze * maze, float gamma) :
	RLAgent(maze),
	gamma_(gamma)
{ }

/*
 * act in the maze environment and learn from it
 */
void QAgent::act()
{

	Maze::location_t current_loc = maze_.get_location();
	//Choose the action

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
