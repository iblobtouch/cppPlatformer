#pragma once
#define _USE_MATH_DEFINES
#include "Point.h"
#include <cmath>
#include <string>
#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

Point::Point(double x, double y) {
	Point::x = x;
	Point::y = y;
}

Point::Point() {
	Point::x = 0.0;
	Point::y = 0.0;
}

double Point::toRadians(double angle) {
	 return angle * (M_PI / 180);
}

void Point::setPoint(double x, double y) {
	this->x = x;
	this->y = y;
}

void Point::setPoint(Point* p) {
	x = p->getX();
	y = p->getY();
}

void Point::add(double x, double y) {
	this->x += x;
	this->y += y;
}

void Point::add(Point* p) {
	x += p->getX();
	y += p->getY();
}

double Point::getX() {
	return x;
}

double Point::getY() {
	return y;
}

double Point::getAngle (Point* p) {
	double theta = atan2(p->y - y, p->x - x);
	if (theta < 0) {
		theta = toRadians(360) + theta;
	}
	return theta;
}

double Point::getDistance(Point* p) {
	return sqrt(pow(abs(x - p->x), 2) + pow(abs(y - p->y), 2));
}
