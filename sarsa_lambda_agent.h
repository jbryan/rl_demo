/*
 *	Author: Josh Bryan <josh.bryan@gmail.com>
 *	This file is copyright 2010 by Josh Bryan.
 *
 *  This file is part of Reinforcement Learning Demo.
 *
 *  Foobar is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any later
 *  version.
 *
 *  Foobar is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

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
