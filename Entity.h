#pragma once
#include "Point.h";

class Entity {
protected:
	const double gravity = 0.05;
	double speed = 2;
	double terminalVelocity = 4;
	Point* pos;
	Point* accel;
public:
	Entity();
	Entity(Point* pos, Point* a);
	void update();
};

