#include "Bullet.h"

Bullet::Bullet(const Bullet& bulletProto)
	: Entity (new Point(*bulletProto.pos), new Point(*bulletProto.accel), bulletProto.entityImages, { bulletProto.entityScreenRect.w / bulletProto.imgScale, bulletProto.entityScreenRect.h / bulletProto.imgScale }, bulletProto.imgScale){
	team = bulletProto.team;
	lifetime = 100;
	visible = true;
	angle = 0.0;
	speed = bulletProto.speed;
}

Bullet::Bullet(std::vector<ReadableTexture*>* bulletImages, SDL_Point bulletImgSize, Point* bulletPos, double bulletSpeed, int scale)
	: Entity(bulletImages, bulletImgSize, scale) {
	team = 0;
	lifetime = 100;
	visible = true;
	angle = 0.0;
	speed = bulletSpeed;
}

void Bullet::update() {
	lifetime -= 1;
	if (lifetime <= 0) {
		visible = false;
	}
	else {
		Entity::update();
	}
}