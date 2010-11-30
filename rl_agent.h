#ifndef RL_AGENT_H_
#define RL_AGENT_H_

#include <boost/multi_array.hpp>
#include "maze.h"

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

		long time_step_;

		virtual float alpha( Maze::location_t const & s, Maze::action_t a);

		//convenience functions for accessing q values
		float& q( Maze::location_t const & s, Maze::action_t a);
		float const& q( Maze::location_t const & s, Maze::action_t a) const;

		float max_over_actions( Maze::location_t const & s) const;
		Maze::action_t argmax_over_actions( Maze::location_t const & s) const;

		virtual Maze::action_t choose_action( Maze::location_t const & s);

};

#endif
