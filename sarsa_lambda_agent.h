#ifndef SARSA_LAMBDA_AGENT_H_
#define SARSA_LAMBDA_AGENT_H_

#include <boost/multi_array.hpp>
#include "rl_agent.h"
#include "maze.h"

class SarsaLambdaAgent :
	public RLAgent
{
	public:
		SarsaLambdaAgent(Maze * maze, float gamma, float lambda);
		SarsaLambdaAgent(Maze * maze);
		virtual ~SarsaLambdaAgent() {}

		virtual void act();

	private:
		//discount factor
		float gamma_; 
		float lambda_;

		//learning rate
		float alpha_;
};

#endif
