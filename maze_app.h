#ifndef MAZE_APP_H_
#define MAZE_APP_H_

#include "sdl_app.h"

#include "maze.h"
#include "q_agent.h"
#include "sarsa_lambda_agent.h"

/*
 * An extension of SdlApp to implement the main
 * drawing loop for this reinforcement learning demo
 */
class MazeApp : public SdlApp
{
	public:
		MazeApp();
		virtual ~MazeApp();

	protected:
		virtual void draw_scene();

	private:
		float theta;

		// The maze for the q agent
		Maze q_maze;
		// The maze for the sarsa agent
		Maze sarsa_maze;
		// The q agent
		QAgent q_agent;
		// The sarsa-lambda agent
		SarsaLambdaAgent sarsa_agent;

};
#endif
