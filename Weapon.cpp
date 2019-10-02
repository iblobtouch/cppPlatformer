#include "Weapon.h"

Weapon::Weapon(std::vector<ReadableTexture*>* weaponImages, SDL_Point weaponImgSize, SDL_Point weaponMountPos, int weaponScale, 
	std::shared_ptr<std::vector<std::unique_ptr<Bullet>>> bullets, Bullet* bulletProto)
	: Entity(weaponImages, weaponImgSize, weaponScale) {
	mount = weaponMountPos;
	maxFiringDelay = 10;
	curFiringDelay = maxFiringDelay;
	bulletStorage = bullets;
	Weapon::bulletProto = bulletProto;
}

void Weapon::mountToPoint(SDL_Rect mountedUnitRect, SDL_Point mountPos, SDL_RendererFlip flip) {
	if (flip == SDL_FLIP_NONE) {
		entityScreenRect.x = mountedUnitRect.x + (mountPos.x * imgScale) - (mount.x * imgScale);
		entityScreenRect.y = mountedUnitRect.y + (mountPos.y * imgScale) - (mount.y * imgScale);
	}
	else if (flip == SDL_FLIP_HORIZONTAL) {
		entityScreenRect.x = mountedUnitRect.x + mountedUnitRect.w - (mountPos.x * imgScale) - (mount.x * imgScale);
		entityScreenRect.y = mountedUnitRect.y + (mountPos.y * imgScale) - (mount.y * imgScale);
	}
}

SDL_Point Weapon::getMountPos() {
	//return { entityScreenRect.x - (mount.x * imgScale), entityScreenRect.y - (mount.y * imgScale) };
	return SDL_Point{ (mount.x * imgScale), (mount.y * imgScale) };
}

SDL_Point Weapon::getMountOnEntity() {
	return { entityScreenRect.x + (mount.x * imgScale), entityScreenRect.y + (mount.y * imgScale) };
}

void Weapon::update() {
	curFiringDelay -= 1;
	int x, y;
	if (curFiringDelay <= 0 && SDL_GetMouseState(&x, &y) == SDL_BUTTON(SDL_BUTTON_LEFT)) {
		curFiringDelay = maxFiringDelay;
		SDL_Point origin = getMountOnEntity();

		int mx = 0, my = 0;
		SDL_GetMouseState(&mx, &my);

		bulletStorage->push_back(std::make_unique<Bullet>(*bulletProto));
		bulletStorage->back()->getPosition()->setPoint(origin.x, origin.y);
		double angle = bulletStorage->back()->getPosition()->getAngle({ mx, my });
		bulletStorage->back()->angle = Point::toDegrees(angle);
		bulletStorage->back()->getPosition()->moveInDirection(entityScreenRect.w - 80, angle);
		bulletStorage->back()->getAccel()->setPoint(Point::setAccelToPoint(origin, { mx, my }, 10));
	}
}
