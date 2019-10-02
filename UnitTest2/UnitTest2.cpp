#include "pch.h"
#include "CppUnitTest.h"
#include "..//Point.h"
#include "..//Point.cpp"
#include "..//sdl_app.h"
#include "..//ReadableTexture.h"
#include "..//ReadableTexture.cpp"
#include "..//player.h"
#include "..//player.cpp"
#include "..//Entity.h"
#include "..//Entity.cpp"
//#include "..//adl_app.cpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <sdl_app.h>
#include <SDL.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(PointsTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Point* p = new Point();
			Assert::AreEqual(p->getX(), 0.0);
		}

		TEST_METHOD(TestMethod2) {
			sdl_app* myapp = new sdl_app(800, 600, false);
			std::tuple<int, int> playerMount = myapp->myPlayer->playerImages.at(0)->findMatchingPixel(SDL_MapRGB(myapp->myPlayer->playerImages.at(0)->getMappingFormat(), 0xFF, 0x00, 0x00));
			std::tuple<int, int> weaponMount = myapp->myPlayer->weaponImage->findMatchingPixel(SDL_MapRGB(myapp->myPlayer->weaponImage->getMappingFormat(), 0xFF, 0x00, 0x00));

			Assert::AreEqual(std::get<0>(playerMount), 28);
			Assert::AreEqual(std::get<1>(playerMount), 89);
		}
	};
}
