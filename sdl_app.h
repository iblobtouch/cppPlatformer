#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "player.h"
#include "Point.h"
#include "Bullet.h"
#include <iostream>
#include <cmath>

class sdl_app {
public: 
	sdl_app(int SCREEN_WIDTH, int SCREEN_HEIGHT);
	int update();
	std::shared_ptr<std::vector<std::unique_ptr<Bullet>>> bullets;
	std::vector<ReadableTexture*> playerTextures;
	std::vector<ReadableTexture*> weaponTextures;
	std::vector<ReadableTexture*> bulletTextures;
	Bullet* bulletProto;
	Weapon* weaponProto;
protected:
	Point* mousePos = NULL;
	SDL_Window* window = NULL;
	SDL_Renderer* gRenderer = NULL;
	player* myPlayer = NULL;
};

