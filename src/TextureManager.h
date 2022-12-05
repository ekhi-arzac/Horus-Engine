#pragma once

#include "Game.h"

class TextureManager
{
public:
	static SDL_Texture* loadTexture(const char* path)
	{
		return IMG_LoadTexture(Game::renderer, path);
	};

	static void draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
	};
};

