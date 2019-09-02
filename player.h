#pragma once
#include "Entity.h"
#include "Point.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class player: public Entity {
	public: 
		player(SDL_Texture* image);
		bool onGround = false;
		void update();
		SDL_Rect entityScreenRect, entityImageClip;
		int curFrame;
		SDL_Texture* getCurrentPlayerImage();
	protected:
		SDL_Texture* entityImage;
};
