#pragma once
#include "Entity.h"
#include "Bullet.h"
class Weapon : public Entity {
	public:
		Weapon(std::vector<ReadableTexture*>* weaponImages, SDL_Point weaponImgSize, SDL_Point weaponMountPos, int scale, std::shared_ptr<std::vector<std::unique_ptr<Bullet>>> bullets, Bullet* bulletProto);
		SDL_Point mount;
		void mountToPoint(SDL_Rect mountedUnitRect, SDL_Point mountPos, SDL_RendererFlip flip);
		SDL_Point getMountPos();
		SDL_Point getMountOnEntity();
		std::shared_ptr<std::vector<std::unique_ptr<Bullet>>> bulletStorage;
		Bullet* bulletProto;
		void update();
	protected:
		int maxFiringDelay;
		int curFiringDelay;
};

