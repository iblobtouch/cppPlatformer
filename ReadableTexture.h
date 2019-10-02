#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Texture wrapper class
class ReadableTexture {
	public:
		ReadableTexture();
		ReadableTexture(std::string path, SDL_Window* curWindow, SDL_Renderer* curRenderer);

	//Gets image dimensions
	int getWidth();
	int getHeight();

	//Pixel manipulators
	Uint32* getPixels();
	int getPitch();
	SDL_PixelFormat* getMappingFormat();
	SDL_Texture* getTexture();

	/// <summary>
	/// Finds the first pixel, reading left to right, that matches the colour given.
	/// </summary>
	/// <returns>The x and y position of a matching pixel, or -1, -1 for pixel not found.</returns>
	SDL_Point findMatchingPixel(Uint32 targetColour);
	SDL_Point findMatchingPixel(Uint32 targetColour, SDL_Rect* region);

	private:
	//The actual hardware texture
	SDL_Surface* baseSurface;
	SDL_Texture* baseTexture;
	int mPitch;
	SDL_PixelFormat* mappingFormat;

	//Image dimensions
	int mWidth;
	int mHeight;
};
