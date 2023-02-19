#include "Objects.h"

#define WINWID 1000
#define WINHEI 800

World* window = nullptr;


int main()
{

	////============================================


	window = new World(WINWID, WINHEI, "ZA WARUDU");

	SetTargetFPS(60);

	auto& gamePadd1 = window->addObject<Paddle>(20.f, 0.f, 'l');
	auto& gamePadd2 = window->addObject<Paddle>(GetScreenWidth() - 40.f, 0.f, 'r');
	auto& gameBall = window->addObject<Ball>(35.f, 0.f, &gamePadd1, &gamePadd2);


	window->initAll();

	while (!WindowShouldClose())
	{

		window->updateAll();


		BeginDrawing();
		ClearBackground(BLACK);

		window->drawAll();

		EndDrawing();

	}

	window->unloadTexAll();
	CloseWindow();

	return 0;
}