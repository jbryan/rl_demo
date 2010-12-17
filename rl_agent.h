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

#ifndef RL_AGENT_H_
#define RL_AGENT_H_

#include <boost/multi_array.hpp>
#include "maze.h"

/*
 * Base class from which other Reinforcement Learning agents 
 * derive
 */
class RLAgent
{
	public:
		RLAgent(Maze * maze);
		virtual ~RLAgent() {}

		typedef boost::multi_array<float,3> value_t;
		typedef boost::multi_array<unsigned long,3> visits_t;
		typedef boost::array<value_t::index,3> index_t;

		virtual void act() = 0;
		virtual void reset_value();
		virtual void draw_policy() const;
	protected:
		Maze & maze_;
		value_t q_values_;
		visits_t visits_;

		virtual float alpha( Maze::location_t const & s, Maze::action_t a);

		//convenience functions for accessing q values
		float& q( Maze::location_t const & s, Maze::action_t a);
		float const& q( Maze::location_t const & s, Maze::action_t a) const;

		float max_over_actions( Maze::location_t const & s) const;
		Maze::action_t argmax_over_actions( Maze::location_t const & s) const;
		unsigned long& visits( Maze::location_t const & s, Maze::action_t a);

		virtual Maze::action_t choose_action( Maze::location_t const & s);

};

#endif
