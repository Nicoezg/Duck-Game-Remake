/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include "graphic/game.h"
#include <iostream>
#include <ostream>
#include <string>


int main( int argc, char* args[] )
{
	std::cout << argc << std::endl;
	if (args[1] == NULL){

	}
	Client client(0);
	Game game(client);
	game.start();
	return 0;
}
