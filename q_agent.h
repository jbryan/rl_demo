
#ifndef Q_AGENT_H_
#define Q_AGENT_H_

#include <boost/multi_array.hpp>
#include "maze.h"

class QAgent
{
	public:
		typedef boost::multi_array<float,3> value_t;
		typedef boost::array<value_t::index,3> value_index_t;

		QAgent(Maze * maze, float gamma);
		QAgent(Maze * maze);
		virtual ~QAgent() {}

		virtual void act();

	private:
		//discount factor
		float gamma_; 

		//learning rate
		float alpha_;
		Maze & maze_;
		value_t q_values_;
};

#endif
