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
