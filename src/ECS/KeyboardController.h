#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

#include <SDL2/SDL.h>

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;


	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;	
				sprite->play("Jump", true);
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->play("Walk", false);
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->play("Walk", false);
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->play("Walk", false);
				break;
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->play("Idle", false);
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->play("Idle", false);
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->play("Idle", false);
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
			default:
				break;
			}
		}
	}
};