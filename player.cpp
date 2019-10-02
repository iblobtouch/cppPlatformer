#include "player.h"

player::player(std::vector<ReadableTexture*>* playerImages, SDL_Point playerImgSize, int scale, Weapon* weapon) : 
	Entity(playerImages, playerImgSize, scale) {
	curWeapon = weapon;
}

void player::update() {
	if (accel->getY() < 4) {
		accel->y += 0.1;
	}

	if (pos->x > (int)800 - entityScreenRect.w) {
		pos->x = (int)800 - entityScreenRect.w;
		accel->x = 0;
	} else if (pos->x < 0) {
		accel->x = 0;
		pos->x = 0;
	}

	if (pos->y > (int)600 - entityScreenRect.h) {
		pos->y = (int)600 - entityScreenRect.h;
		accel->y = 0;
		onGround = true;
	}

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP] && onGround) {
		accel->y = -terminalVelocity;
		onGround = false;
	}
	if (flip == SDL_FLIP_NONE) {
		if (currentKeyStates[SDL_SCANCODE_LEFT]) {
			accel->x = -speed;
			curState = WALKINGSTATE;
			curFrame -= 1;
		}
		else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
			accel->x = speed;
			curState = WALKINGSTATE;
			curFrame += 1;
		} else {
			accel->x = 0;
			curState = STANDINGSTATE;
		}
	}
	else {
		if (currentKeyStates[SDL_SCANCODE_LEFT]) {
			accel->x = -speed;
			curState = WALKINGSTATE;
			curFrame += 1;
		}
		else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
			accel->x = speed;
			curState = WALKINGSTATE;
			curFrame -= 1;
		} else {
			accel->x = 0;
			curState = STANDINGSTATE;
		}
	}

	if (curFrame < 0) {
		curFrame = (entityClipRects[curState].size()) * (ANIMATIONSLOW) - 1;
	}

	if (curFrame > (entityClipRects[curState].size()) * (ANIMATIONSLOW) - 1) {
		curFrame = 0;
	}

	curWeapon->mountToPoint(entityScreenRect, entityImages->at(curState)->findMatchingPixel(SDL_MapRGB(entityImages->at(curState)->getMappingFormat(), 0xFF, 0, 0), getCurrentClip()), flip);

	int mx = 0, my = 0;
	SDL_GetMouseState(&mx, &my);

	if (mx > entityScreenRect.x) {
		flip = SDL_FLIP_NONE;
	}
	else {
		flip = SDL_FLIP_HORIZONTAL;
	}

	Entity::update();
	curWeapon->update();
}

Weapon* player::getCurWeapon() {
	return curWeapon;
}
