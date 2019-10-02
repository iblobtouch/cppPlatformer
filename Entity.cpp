#include "Entity.h"

std::vector<SDL_Rect> Entity::generateRectsFromSheet(ReadableTexture* sheet, SDL_Point imgSize) {
	int sw = sheet->getWidth(), sh = sheet->getHeight();
	std::vector<SDL_Rect> result;
	for (int y = 0; y < sh; y += imgSize.y) {
		for (int x = 0; x < sw; x += imgSize.x) {
			SDL_Rect tempRect = { x, y, imgSize.x, imgSize.y };
			result.push_back(tempRect);
		}
	}

	return result;
}

Entity::Entity(std::vector<ReadableTexture*>* images, SDL_Point imgSize, int imgScale) {
	pos = new Point();
	accel = new Point();
	Entity::imgScale = imgScale;
	entityScreenRect = { 0, 0, imgSize.x * imgScale, imgSize.y * imgScale };

	entityImages = images;
	for (int i = 0; i < entityImages->size(); i += 1) {
		entityClipRects.push_back(generateRectsFromSheet(entityImages->at(i), imgSize));
	}
}

Entity::Entity(Point* pos, Point* a, std::vector<ReadableTexture*>* images, SDL_Point imgSize, int imgScale) {
	Entity::pos = pos;
	Entity::accel = a;
	Entity::imgScale = imgScale;
	entityScreenRect = { 0, 0, imgSize.x * imgScale, imgSize.y * imgScale };

	entityImages = images;
	for (int i = 0; i < entityImages->size(); i += 1) {
		entityClipRects.push_back(generateRectsFromSheet(entityImages->at(i), imgSize));
	}

}

void Entity::update() {
	pos->add(accel);

	entityScreenRect.x = trunc(pos->x);
	entityScreenRect.y = trunc(pos->y);
}

std::vector<ReadableTexture*>* Entity::getImages() {
	return entityImages;
}

SDL_Point Entity::getImgSize() {
	return { entityScreenRect.w / imgScale, entityScreenRect.h / imgScale };
}

int Entity::getImgScale() {
	return imgScale;
}

SDL_Texture* Entity::getCurrentImage() {
	return entityImages->at(curState)->getTexture();
}

SDL_Rect* Entity::getCurrentClip() {
	return entityClipRects[curState].data() + (curFrame / (ANIMATIONSLOW));
}

SDL_Rect Entity::getScreenRect() {
	return entityScreenRect;
}

Point* Entity::getPosition() {
	return pos;
}

Point* Entity::getAccel() {
	return accel;
}


