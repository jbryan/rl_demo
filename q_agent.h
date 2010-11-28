
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
		virtual void reset_value();
		virtual void draw_policy() const;

	private:
		//discount factor
		float gamma_; 

		//learning rate
		float alpha_;
		Maze & maze_;
		value_t q_values_;

		float& q( Maze::location_t const & s, Maze::action_t a);
		float const& q( Maze::location_t const & s, Maze::action_t a) const;
		float max_over_actions( Maze::location_t const & s) const;
		Maze::action_t argmax_over_actions( Maze::location_t const & s) const;
};

#endif
