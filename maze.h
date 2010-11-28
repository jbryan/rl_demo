
#ifndef MAZE_H_
#define MAZE_H_

#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/multi_array.hpp>

class Maze
{
	public:
		typedef boost::multi_array<float,2> grid_t;
		typedef boost::array<grid_t::index,2> location_t;

		typedef enum 
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		} action_t;

		Maze(int x, int y);
		virtual ~Maze() {}

		virtual void draw_maze();
		virtual float perform_action(action_t action);
		location_t const &get_location() const { return location; };
		

	private:
		grid_t grid;
		location_t location;
};

#endif
