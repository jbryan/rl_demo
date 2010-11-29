#ifndef Q_AGENT_H_
#define Q_AGENT_H_

#include <boost/multi_array.hpp>
#include "rl_agent.h"
#include "maze.h"

class QAgent :
	public RLAgent
{
	public:
		QAgent(Maze * maze, float gamma);
		QAgent(Maze * maze);
		virtual ~QAgent() {}

		virtual void act();

	private:
		//discount factor
		float gamma_; 

		//learning rate
		float alpha_;
};

#endif
