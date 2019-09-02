#include <SDL.h>
#include "sdl_app.h"
#include "player.h"
#include "SDL_image.h"
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* args[]) {
	sdl_app* myapp;
	player* myGuy;
	try {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			throw std::string("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		}
		// load support for the JPG and PNG image formats
		int flags = IMG_INIT_JPG | IMG_INIT_PNG;
		int initted = IMG_Init(flags);
		if ((initted & flags) != flags) {
			printf("IMG_Init: Failed to init required jpg and png support!\n");
			printf("IMG_Init: %s\n", IMG_GetError());
			// handle error
		}
		 myapp = new sdl_app(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	} catch (std::string errorS) {
		std::cout << errorS << std::endl;

		//Quit SDL subsystems
		SDL_Quit();

		return 0;
	}
	while (1) {
		if (myapp->update() == 0) {
			return 0;
		}
	}
}