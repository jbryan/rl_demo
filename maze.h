
#ifndef MAZE_H_
#define MAZE_H_

#include <vector>
#include <boost/multi_array.hpp>

class Maze
{
	public:
		typedef boost::multi_array<float,2> grid_t;
		typedef boost::array<grid_t::index,2> location_t;

		enum action_t 
		{
			UP,
			DOWN,
			LEFT,
			RIGHT,
			NUM_ACT,
			MIN_ACT=UP
		};

		Maze(int x, int y);
		virtual ~Maze() {}

		virtual void draw_maze() const;
		virtual float perform_action(action_t action);
		location_t const &get_location() const { return location; };
		unsigned int get_width() const ;
		unsigned int get_height() const ;
		

	private:
		grid_t grid;
		location_t location;
};

#endif