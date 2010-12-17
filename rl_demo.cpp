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


#include "maze_app.h"

/*
 * Main entry point ... create the app, and run it.
 */
int main( int argc, char **argv )
{
	try
	{
		MazeApp app;
		app.init();
		app.run_loop();
		return 0;
	}
	catch (...) 
	{
		return -1;
	}
}
