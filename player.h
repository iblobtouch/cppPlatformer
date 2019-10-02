#pragma once
#include "Entity.h"
#include "Point.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Weapon.h"

class player: public Entity {
	public: 
		player(std::vector<ReadableTexture*>* playerImages, SDL_Point playerImgSize, int scale, Weapon* weapon);
		bool onGround = false;
		void update();
		Weapon* getCurWeapon();
		SDL_RendererFlip flip = SDL_FLIP_NONE;
	protected:
		Weapon* curWeapon;
};
