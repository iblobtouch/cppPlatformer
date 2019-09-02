#include "player.h"

enum playerInfo {
	PLAYERIMAGEWIDTH = 64,
	PLAYERIMAGEHEIGHT = 64,

	PLAYERIMAGECLIPWIDTH = 44,
	PLAYERIMAGECLIPHEIGHT = 48,

	ANIMATIONSPEED = 30,
	ANIMATIONFRAMES = 4
};

player::player(SDL_Texture* image) {
	player::pos = new Point();
	player::accel = new Point();
	entityImage = image;
	entityScreenRect.x = 0;
	entityScreenRect.y = 0;
	entityScreenRect.w = PLAYERIMAGEWIDTH;
	entityScreenRect.h = PLAYERIMAGEHEIGHT;

	entityImageClip.x = 0;
	entityImageClip.y = 0;
	entityImageClip.w = PLAYERIMAGECLIPWIDTH;
	entityImageClip.h = PLAYERIMAGECLIPHEIGHT;

	player::curFrame = 0;


	if (!entityImage) {
		//throw std::string("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}
}

void player::update() {
	if (accel->getY() < 4) {
		accel->y += 0.1;
	}

	if (pos->x > 800 - PLAYERIMAGEWIDTH) {
		pos->x = 800 - PLAYERIMAGEWIDTH;
		accel->x = 0;
	} else if (pos->x < 0) {
		accel->x = 0;
		pos->x = 0;
	}

	if (pos->y > 600 - PLAYERIMAGEHEIGHT) {
		pos->y = 600 - PLAYERIMAGEHEIGHT;
		accel->y = 0;
		onGround = true;
	}

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP] && onGround) {
		accel->y = -terminalVelocity;
		onGround = false;
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		accel->x = -speed;
		curFrame -= 1;
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		accel->x = speed;
		curFrame += 1;
	}
	else {
		accel->x = 0;
	}

	if (curFrame > ANIMATIONSPEED - 1) {
		curFrame = 0;
	}
	if (curFrame < 0) {
		curFrame = ANIMATIONSPEED - 1;
	}
	entityScreenRect.x = round(pos->x);
	entityScreenRect.y = round(pos->y);

	entityImageClip.x = entityImageClip.w * floor(curFrame / (ANIMATIONSPEED / ANIMATIONFRAMES));
	if (entityImageClip.x > entityImageClip.w * (ANIMATIONFRAMES - 1)) {
		entityImageClip.x = entityImageClip.w * (ANIMATIONFRAMES - 1);
	}
	Entity::update();
}

SDL_Texture* player::getCurrentPlayerImage() {
	return entityImage;
}
