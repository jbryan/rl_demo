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

#ifndef SDL_APP_H_
#define SDL_APP_H_

#include "SDL.h"

/*
 * A base class that can be used for setting up simple
 * SDL apps.
 */
class SdlApp
{
	public:
		SdlApp();
		virtual ~SdlApp();

		virtual void init();
		virtual void tear_down();
		virtual void step();
		virtual void run_loop();

	protected:
		virtual void draw_scene() {}
		virtual void handle_key_press( SDL_keysym *keysym);

	private:
		SDL_Surface *surface;
		bool running;
};
#endif
