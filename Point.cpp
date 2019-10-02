#pragma once
#define _USE_MATH_DEFINES
#include "Point.h"
#include <cmath>
#include <string>
#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

Point::Point(const Point& oldPoint) {
	x = oldPoint.x;
	y = oldPoint.y;
}

Point::Point(double x, double y) {
	Point::x = x;
	Point::y = y;
}

Point::Point() {
	Point::x = 0.0;
	Point::y = 0.0;
}

double Point::toRadians(double degrees) {
	 return degrees * (M_PI / 180);
}

double Point::toDegrees(double radians) {
	return radians * (180 / M_PI);
}

void Point::setPoint(double x, double y) {
	this->x = x;
	this->y = y;
}

void Point::setPoint(Point* p) {
	x = p->getX();
	y = p->getY();
}

void Point::setPoint(PointVals p) {
	x = p.x;
	y = p.y;
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

SDL_Point Point::getAsSDLPoint() {
	return {(int)trunc(x), (int)trunc(y) };
}

double Point::getAngle (Point* p) {
	double theta = atan2(p->y - y, p->x - x);
	if (theta < 0) {
		theta = toRadians(360) + theta;
	}
	return theta;
}

double Point::getAngle(SDL_Point p) {
	double theta = atan2(p.y - y, p.x - x);
	if (theta < 0) {
		theta = toRadians(360) + theta;
	}
	return theta;
}

PointVals Point::setAccelToPoint(Point* source, SDL_Point target, double speed) {
	//Returns the accel to move to a given point by a given speed.
	PointVals res = { 0, 0 };
	res.x = speed * cos(source->getAngle(target));
	res.y = speed * sin(source->getAngle(target));
	return res;
}

PointVals Point::setAccelToPoint(SDL_Point source, SDL_Point target, double speed) {
	//Returns the accel to move to a given point by a given speed.
	PointVals res = { 0, 0 };
	double theta = atan2(target.y - source.y, target.x - source.x);
	if (theta < 0) {
		theta = toRadians(360) + theta;
	}
	res.x = speed * cos(theta);
	res.y = speed * sin(theta);
	return res;
}

void Point::moveInDirection(int distance, double angle) {
	x += distance * cos(angle);
	y += distance * sin(angle);
}

double Point::getDistance(Point* p) {
	return sqrt(pow(abs(x - p->x), 2) + pow(abs(y - p->y), 2));
}
