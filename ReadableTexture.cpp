#include "ReadableTexture.h"

ReadableTexture::ReadableTexture()
{
	//Initialize
	mWidth = 0;
	mHeight = 0;
	mPitch = 0;
	mappingFormat = NULL;
	baseSurface = NULL;
	baseTexture = NULL;
}

ReadableTexture::ReadableTexture(std::string path, SDL_Window* curWindow, SDL_Renderer* curRenderer) {

	//Allocate format from window
	Uint32 format = SDL_GetWindowPixelFormat(curWindow);
	mappingFormat = SDL_AllocFormat(format);

	//Load image at specified path
	baseSurface = IMG_Load( path.c_str() );
		//Convert surface to display format
		baseSurface = SDL_ConvertSurfaceFormat(baseSurface, SDL_GetWindowPixelFormat(curWindow), 0 );
		if(baseSurface == NULL ) {
			printf( "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError() );
		}
		Uint32 colorkey = SDL_MapRGB(baseSurface->format, 0xFF, 0xFF, 0xFF);
		SDL_SetColorKey(baseSurface, SDL_TRUE, colorkey);

		baseTexture = SDL_CreateTextureFromSurface(curRenderer, baseSurface);
		SDL_SetTextureBlendMode(baseTexture, SDL_BLENDMODE_BLEND);

		mWidth = baseSurface->w;
		mHeight = baseSurface->h;
		mPitch = baseSurface->pitch;
		mappingFormat = baseSurface->format;
}

int ReadableTexture::getWidth()
{
	return mWidth;
}

int ReadableTexture::getHeight()
{
	return mHeight;
}

Uint32* ReadableTexture::getPixels() {
	return (Uint32*)baseSurface->pixels;
}

SDL_Texture* ReadableTexture::getTexture() {
	return baseTexture;
}

int ReadableTexture::getPitch()
{
	return mPitch;
}

SDL_PixelFormat* ReadableTexture::getMappingFormat() {
	return mappingFormat;
}

SDL_Point ReadableTexture::findMatchingPixel(Uint32 targetColour) {
	Uint32* pImage = getPixels();
	int pixelCount = (mPitch / 4) * mHeight;

	for (int i = 0; i < pixelCount; i += 1) {
		if (pImage[i] == targetColour) {
			return { i % mWidth, i / mWidth };
		}
	}
	return { -500, -500 };
}

SDL_Point ReadableTexture::findMatchingPixel(Uint32 targetColour, SDL_Rect* region) {
	Uint32* pImage = getPixels();
	int pixelCount = (mPitch / 4) * mHeight, i = 0;

	for (int y = region->y; y < region->y + region->h; y += 1) {
		for (int x = region->x; x < region->x + region->w; x += 1) {
			int i = x + (y * mWidth);
			if (pImage[i] == targetColour) {
				return { x - region->x, y - region->y };
			}
		}
	}
	return { -100, -100 };
}