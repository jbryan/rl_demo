
#ifndef Q_AGENT_H_
#define Q_AGENT_H_

#include "maze.h"

class QAgent
{
	public:
		QAgent(Maze * maze);
		virtual ~QAgent() {}

		virtual void act();

	private:
		Maze & maze_;
};

#endif
