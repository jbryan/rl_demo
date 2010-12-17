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
