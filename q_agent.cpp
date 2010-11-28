
#include <vector>
#include "q_agent.h"
#include "discrete.h"

QAgent::QAgent(Maze * maze) :
	maze_(*maze)
{}

void QAgent::act()
{
	std::vector<double> probs(4,1.0);
	DiscreteVariate choose(probs);


	maze_.perform_action((Maze::action_t) choose());
}

