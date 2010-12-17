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
