#include "sdl_app.h"

sdl_app::sdl_app(int SCREEN_WIDTH, int SCREEN_HEIGHT) {
	mousePos = new Point();
	window = SDL_CreateWindow("Test Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		throw std::string("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		//Create renderer for window
		gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (gRenderer == NULL) {
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else {
			//Initialize renderer color
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0);
			SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			}
		}
	}

	bullets = std::make_shared<std::vector<std::unique_ptr<Bullet>>>();

	try {
		playerTextures = { new ReadableTexture("images/MechStand.png", window, gRenderer), new ReadableTexture("images/MechWalkFit.png", window, gRenderer) };
		weaponTextures = { new ReadableTexture("images/Weapon.png", window, gRenderer)};
		//std::vector of pointers to texture objects, this vector is a field of the class it's being defined in.
		bulletTextures = { new ReadableTexture("images/Bullet.png", window, gRenderer) };
		//Pass the textures to the bullet by reference, however the pointer recieved in the constructor is NULL (0xccccccccccc)?
		bulletProto = new Bullet(&bulletTextures, { 8, 4 }, new Point, 10, 2);
		weaponProto = new Weapon(&weaponTextures, { 64, 64 }, { 19, 29 }, 2, bullets, bulletProto);
		myPlayer = new player(&playerTextures, { 47, 55 }, 2, weaponProto);
	}
	catch (std::string errorS) {
		throw std::string("Could not find the player image: %s\n", SDL_GetError());
	}
}

int sdl_app::update() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_WINDOWEVENT) {
			switch (event.window.event) {
			case SDL_WINDOWEVENT_CLOSE:
				if (event.window.windowID == SDL_GetWindowID(this->window)) {
					//Quit SDL subsystems
					SDL_Quit();
					return 0;
				}
			}
		}
	}
	int mx = 0, my = 0;
	SDL_GetMouseState(&mx, &my);
	mousePos->setPoint(mx, my);

	myPlayer->update();
	//Clear screen
	SDL_RenderClear(gRenderer);

	//Render texture to screen

	double angle = Point::toDegrees(mousePos->getAngle(myPlayer->getCurWeapon()->getMountOnEntity())) + 180;

	SDL_RenderCopyEx(gRenderer, myPlayer->getCurrentImage(), myPlayer->getCurrentClip(), &myPlayer->getScreenRect(), 0.0, NULL, myPlayer->flip);

	for (int i = 0; i < bullets->size(); i += 1) {
		if (bullets->at(i)->visible == true) {
			bullets->at(i)->update();
			SDL_RenderCopyEx(gRenderer, bullets->at(i)->getCurrentImage(), bullets->at(i)->getCurrentClip(), &bullets->at(i)->getScreenRect(), bullets->at(i)->angle, NULL, SDL_FLIP_NONE);
		}
	}

	SDL_RenderCopyEx(gRenderer, myPlayer->getCurWeapon()->getCurrentImage(), myPlayer->getCurWeapon()->getCurrentClip(), &myPlayer->getCurWeapon()->getScreenRect(), angle, &myPlayer->getCurWeapon()->getMountPos(), SDL_FLIP_NONE);

	//Update screen
	SDL_RenderPresent(gRenderer);

	return 1;
}
