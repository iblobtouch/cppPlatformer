#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "player.h"

class sdl_app {
	//The window we'll be rendering to
	public: SDL_Window* window = NULL;

	public: SDL_RWops* rwop;

	//The window renderer
	public: SDL_Renderer* gRenderer = NULL;

	public: player* myPlayer = NULL;

	sdl_app (int SCREEN_WIDTH, int SCREEN_HEIGHT, bool causeError) {
		rwop = SDL_RWFromFile("images/Walk.png", "rb");
			
			//Create window
			window = SDL_CreateWindow("Test Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (window == NULL) {
				throw std::string("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			} else {
				//Create renderer for window
				gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (gRenderer == NULL) {
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				}
				else {
					//Initialize renderer color
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags)) {
						printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					}
				}
			}
			try {
				myPlayer = new player(loadTexture("images/Walk.png"));
			} catch (std::string errorS) {
				throw std::string("Could not find the player image: %s\n", SDL_GetError());
			}
	}

	private: SDL_Texture* loadTexture(std::string path) {
		//The final texture
		SDL_Texture* newTexture = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL) {
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		}
		else {
			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
			if (newTexture == NULL) {
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}

		return newTexture;
	}

	public: int update() {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_WINDOWEVENT) {
				switch (event.window.event) {
				case SDL_WINDOWEVENT_CLOSE:
					if (event.window.windowID == SDL_GetWindowID(this->window)) {
						//Quit SDL subsystems
						SDL_Quit();
						return 0;
					}
				}
			}
		}
		myPlayer->update();
		//Clear screen
		SDL_RenderClear(gRenderer);

		//Render texture to screen
		SDL_RenderCopy(gRenderer, myPlayer->getCurrentPlayerImage(), &myPlayer->entityImageClip, &myPlayer->entityScreenRect);

		//Update screen
		SDL_RenderPresent(gRenderer);

		return 1;
	}
};

