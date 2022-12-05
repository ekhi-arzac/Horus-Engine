#include "Game.h"

constexpr auto WIN_TITLE = "Horus";
constexpr auto WIN_W = 640;
constexpr auto WIN_H = 480;


Game* horus = nullptr;

int main(int argc, char* argv[]) 
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	horus = new Game();
	horus->init(WIN_TITLE, WIN_W, WIN_H, false);

	while(horus->running()) 
	{

		frameStart = SDL_GetTicks();

		horus->handleEvents();
		horus->update();
		horus->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	horus->clean();
	return 0;
}