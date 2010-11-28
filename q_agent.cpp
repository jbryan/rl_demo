
#include <vector>
#include <algorithm>
#include <limits>
#include "q_agent.h"
#include "discrete.h"

QAgent::QAgent(Maze * maze) :
	maze_(*maze), 
	gamma_(0.9),
	alpha_(0.2),
	q_values_(
			boost::extents[maze_.get_width()][maze_.get_height()][Maze::NUM_ACT]
			)
{}

QAgent::QAgent(Maze * maze, float gamma) :
	maze_(*maze), 
	gamma_(gamma),
	alpha_(0.2),
	q_values_(
			boost::extents[maze_.get_width()][maze_.get_height()][Maze::NUM_ACT]
			)
{}

void QAgent::act()
{
	//std::vector<double> probs(4,1.0);
	//DiscreteVariate choose(probs);
	//Maze::action_t action = (Maze::action_t) choose();

	Maze::location_t const loc = maze_.get_location();

	Maze::action_t action;
	float max_value = -std::numeric_limits<float>::max();

	for (Maze::action_t a = Maze::MIN_ACT;  a < Maze::NUM_ACT; a = Maze::action_t(a+1))
	{
		if (q_values_[loc[0]][loc[1]][a] > max_value)
		{
			action = a;
			max_value = q_values_[loc[0]][loc[1]][a];
		}
	}

	float reward = maze_.perform_action(action);
	q_values_[loc[0]][loc[1]][action] += alpha_ * (reward-100 - max_value);
}

