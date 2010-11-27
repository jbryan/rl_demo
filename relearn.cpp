
#include "maze_app.h"


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
