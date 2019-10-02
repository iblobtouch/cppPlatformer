#pragma once
#include <SDL.h>
#include "Point.h"
#include "ReadableTexture.h"
#include <vector>
#include <memory>

enum playerInfo {
	STANDINGSTATE = 0,
	WALKINGSTATE = 1,

	RENDERSCALEFACTOR = 2,

	ANIMATIONSLOW = 8
};

class Entity {
public:
	double gravity = 0.05;
	Entity(std::vector<ReadableTexture*>* images, SDL_Point imgSize, int imgScale);
	Entity(Point* pos, Point* a, std::vector<ReadableTexture*>* images, SDL_Point imgSize, int imgScale);
	void update();
	std::vector<ReadableTexture*>* getImages();
	SDL_Point getImgSize();
	int getImgScale();
	SDL_Texture* getCurrentImage();
	SDL_Rect* getCurrentClip();
	SDL_Rect getScreenRect();
	Point* getPosition();
	Point* getAccel();
protected:
	short curState = 0;
	SDL_Rect entityScreenRect;
	std::vector<ReadableTexture*>* entityImages;
	std::vector<std::vector<SDL_Rect>> entityClipRects;
	int curFrame = 0;
	int imgScale;
	double speed = 2;
	double terminalVelocity = 4;
	Point* pos; 
	Point* accel;
	static std::vector<SDL_Rect> generateRectsFromSheet(ReadableTexture* sheet, SDL_Point imgSize);
};

