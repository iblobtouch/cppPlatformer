#include "Entity.h"

Entity::Entity() {
	pos = new Point();
	accel = new Point();
}

Entity::Entity(Point* pos, Point* a) {
	pos = pos;
	accel = a;
}

void Entity::update() {
	pos->add(accel);
}