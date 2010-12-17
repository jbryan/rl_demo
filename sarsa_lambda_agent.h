#ifndef SARSA_LAMBDA_AGENT_H_
#define SARSA_LAMBDA_AGENT_H_

#include <boost/multi_array.hpp>
#include "rl_agent.h"
#include "maze.h"

/*
 * Implentation of SARSA-lambda agent.
 */
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

		//place to store next action after it has been
		//decided
		Maze::action_t new_act;

		RLAgent::value_t e_values_;

		float& e( Maze::location_t const & s, Maze::action_t a);
		float const& e( Maze::location_t const & s, Maze::action_t a) const;
};

#endif
