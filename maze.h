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


#ifndef MAZE_H_
#define MAZE_H_

#include <vector>
#include <boost/multi_array.hpp>

/*
 * A class to represent the simple maze world that the 
 * learning agents will interact with.
 */
class Maze
{
	public:
		typedef boost::multi_array<float,2> grid_t;
		typedef boost::array<grid_t::index,2> location_t;

		// Action names
		enum action_t 
		{
			UP,
			LEFT,
			DOWN,
			RIGHT,
			MIN_ACT= UP,
			MAX_ACT = RIGHT
		};

		// Number of actions
		static int const NUM_ACT = MAX_ACT + 1;

		Maze(int x, int y);
		virtual ~Maze() {}

		virtual void draw_maze() const;
		virtual float perform_action(action_t action);
		virtual location_t transition(location_t loc, action_t action);

		location_t const &get_location() const { return location; };

		unsigned int get_width() const ;
		unsigned int get_height() const ;
		void set_stochastic_actions( bool stochastic );

	private:
		// array representing the grid world
		grid_t grid;
		// current location of the agent
		location_t location;
		// whether we should use stochastic actions
		bool stochastic_actions_;
};

#endif
