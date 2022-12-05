#pragma once

#include "Components.h";
#include  "Animation.h"
#include "../TextureManager.h";
#include <SDL2/SDL.h>
#include <map>

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 4;
	int speed = 200;
	int currentFrame;

public:
	bool once = false;
	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;


	SpriteComponent() = default;

	SpriteComponent(const char* id)
	{
		setTex(id);
	}

	SpriteComponent(const char* id, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 13, 100);
		Animation walk = Animation(1, 8, 100);
		Animation jump = Animation(5, 6, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);
		animations.emplace("Jump", jump);

		play("Idle", false);

		setTex(id);
	}

	~SpriteComponent()
	{
	}

	void setTex(const char* id)
	{
		texture = TextureManager::loadTexture(id);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.w = destRect.h = 32;
	}

	void update() override
	{	
		currentFrame = static_cast<int>((SDL_GetTicks() / speed) % frames);
		if (animated && !once)
		{
			srcRect.x = srcRect.w * currentFrame;
		}

		if (animated && once)
		{
			srcRect.x = srcRect.w * currentFrame;
			if (currentFrame == frames - 1)
			{
				this->once = false;
				play("Idle", false);
			}
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::draw(texture, srcRect, destRect, spriteFlip);
	}

	void play(const char* animName, bool once)
	{
		if (this->once) 
		{
			return;
		}
		this->once = once;
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;

	}

	void setAnimation(const char* id, Animation anim)
	{
		animations.emplace(id, anim);
	}

 
};

