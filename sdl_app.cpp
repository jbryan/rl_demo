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


#include <string>
#include <stdexcept>
#include <GL/gl.h>
#include <GL/glu.h>

#include "sdl_app.h"

SdlApp::SdlApp() : 
	running(false)
{ }

SdlApp::~SdlApp()
{ 
	tear_down();
}

/*
 * This function sets up the SDL surface and gl options.  Some of this has been
 * borrowed from Ti Leggett's SDL port of Jeff Molofee's opengl examples at 
 * http://nehe.gamedev.net.
 */
void SdlApp::init()
{
	/* Flags to pass to SDL_SetVideoMode */
	int videoFlags;
	const SDL_VideoInfo *videoInfo;

	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		throw std::runtime_error(std::string("Video initialization failed: ") 
			+ SDL_GetError( ));
	}

	/* Fetch the video info */
	videoInfo = SDL_GetVideoInfo( );

	if ( !videoInfo )
	{
		throw std::runtime_error(std::string("Video query failed: ")  
			+ SDL_GetError( ));
	}

	/* the flags to pass to SDL_SetVideoMode */
	videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
	videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
	videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
	videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

	/* This checks to see if surfaces can be stored in memory */
	if ( videoInfo->hw_available )
		videoFlags |= SDL_HWSURFACE;
	else
		videoFlags |= SDL_SWSURFACE;

	/* This checks if hardware blits can be done */
	if ( videoInfo->blit_hw )
		videoFlags |= SDL_HWACCEL;

	videoFlags |= SDL_FULLSCREEN;

	/* Sets up OpenGL double buffering */
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	/* get a SDL surface */
	surface = SDL_SetVideoMode( 0, 0, 32, videoFlags );

	/* Verify there is a surface */
	if ( !surface )
	{
		throw std::runtime_error(std::string("Video mode set failed: ") 
			+ SDL_GetError( ));
	}

	/* initialize OpenGL */
	/* Enable smooth shading */
	glShadeModel( GL_SMOOTH );

	/* Set the background black */
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	/* Depth buffer setup */
	glClearDepth( 1.0f );

	/* Enables Depth Testing */
	glEnable( GL_DEPTH_TEST );

	/* The Type Of Depth Test To Do */
	glDepthFunc( GL_LEQUAL );

	/* Really Nice Perspective Calculations */
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	glEnable (GL_POINT_SMOOTH);
	glEnable (GL_POLYGON_SMOOTH);
	glEnable (GL_LINE_SMOOTH);

	glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint (GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Height / width ration */
	GLfloat ratio = (GLfloat) videoInfo->current_w 
		/ (GLfloat) videoInfo->current_h;
	/* Setup our viewport. */
	glViewport( 0, 0, ( GLsizei )videoInfo->current_w,
			( GLsizei )videoInfo->current_h);

	/* change to the projection matrix and set our viewing volume. */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	/* Set our perspective */
	gluPerspective( 45.0f, ratio, 0.1f, 100.0f );


	/* Make sure we're changing the model view and not the projection */
	glMatrixMode( GL_MODELVIEW );

	/* Reset The View */
	glLoadIdentity( );

	running = true;
}

/*
 * call before quitting
 */
void SdlApp::tear_down()
{
	running = false;
	SDL_Quit();
}

/*
 * Run through one frame drawing cycle
 */
void SdlApp::step()
{
	if (!running) return;

	draw_scene();

	SDL_Event event;
	while ( SDL_PollEvent( &event ) )
	{
		switch( event.type )
		{
			case SDL_ACTIVEEVENT:
				//TODO: handle focus change
				break;			    
			case SDL_KEYDOWN:
				/* handle key presses */
				handle_key_press( &event.key.keysym );
				break;
			case SDL_QUIT:
				/* handle quit requests */
				tear_down();
				break;
			default:
				break;
		}
	}

}

/*
 * iterate the frame loop until done
 */
void SdlApp::run_loop()
{
	while(running)
	{
		step();
	}
}

/*
 * check for key presses
 */
void SdlApp::handle_key_press( SDL_keysym *keysym )
{
	switch ( keysym->sym )
	{
		case SDLK_ESCAPE:
		case SDLK_q:
			tear_down( );
			break;
		default:
			break;
	}
}
