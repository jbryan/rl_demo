#ifndef MAZE_APP_H_
#define MAZE_APP_H_

#include "sdl_app.h"

#include "maze.h"
#include "q_agent.h"

class MazeApp : public SdlApp
{
	public:
		MazeApp();
		virtual ~MazeApp();

	protected:
		virtual void draw_scene();

	private:
		float theta;

		Maze my_maze;
		QAgent agent;

};
#endif
