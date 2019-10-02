#pragma once
#include "Entity.h"
class Bullet : public Entity {
	public:
	Bullet(const Bullet& bulletProto);
	Bullet(std::vector<ReadableTexture*>* bulletImages, SDL_Point bulletImgSize, Point* bulletPos, double bulletSpeed, int scale);
		void update();
		bool visible;
		double angle;
		double speed;
	protected:
		int team;
		int lifetime;
};

