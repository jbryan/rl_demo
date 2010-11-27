
#ifndef MAZE_H_
#define MAZE_H_

#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/multi_array.hpp>

class Maze
{
	public:
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

	private:
		typedef boost::multi_array<float,2> maze_t;

		maze_t maze;
		boost::array<maze_t::index,2> location;
};

#endif
